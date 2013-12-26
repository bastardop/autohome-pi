/*
Copyright 2013 Anton Hammerschmidt

This file is part of PowerPi.

PowerPi is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PowerPi is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with PowerPi.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <syslog.h>

#include "structs.h"
#include "tools.h"
#include "xmlreader.h"
#include "picontrol.h"

#define BUFLEN 512

using namespace std;

string settingsFile = "/etc/default/powerpi";

int port;
int datagpio;
vector<WSocket> sockets;
vector<Gpio> gpios;
vector<Schedule> schedules;

vector<ScheduleTask> scheduleTasks;

pthread_mutex_t socketsMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t gpiosMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t schedulesMutex = PTHREAD_MUTEX_INITIALIZER;

void error(string s) {
    perror(s.c_str());
    exit(1);
}

string readFile(string path) {
    string content;
    ifstream file;
    file.open(path.c_str());
    if(file.is_open()) {
        string line;
        while(!file.eof()) {
            getline(file, line, '\n');
            content.append(line);
        }
    }else
        syslog(LOG_CRIT, "Can't read file: %s", path.c_str());
    file.close();
    return content;
}

void saveFile(string path, string content) {
    ofstream file;
    file.open(path.c_str(), ios::out);
    if(file.is_open())
        file << content;
    else
        syslog(LOG_ERR, "Can't write file: %s", path.c_str());
    file.close();
}

string getSettings() {
    stringstream out;
    out << "Port: " << port;
    out << "Data-Gpio: " << datagpio;

	for(int s=0; s<sockets.size(); s++)
        out << sockets[s].toString();

	for(int g=0; g<gpios.size(); g++)
        out << gpios[g].toString();

	for(int s=0; s<schedules.size(); s++)
        out << schedules[s].toString();

    return out.str();
}

void loadSettings() {
  port = 9999;
  datagpio = 0;
	sockets.clear();
	gpios.clear();
	schedules.clear();

  string settings = readFile(settingsFile);
	XmlReader reader(settings);
	port = reader.getPort();
	datagpio = reader.getDatagpio();
	sockets = reader.getSockets();
	gpios = reader.getGpios();
	schedules = reader.getSchedules();

	syslog(LOG_INFO, "Settings: %s", getSettings().c_str());
}

void saveSettings() {
    string xmldata = XmlReader::generateXml(port, datagpio, sockets, gpios, schedules);
    saveFile(settingsFile, xmldata);
}

string generateList() {
   stringstream out;

    for(int s=0; s<sockets.size(); s++) {
        out << "socket:" << sockets[s].getName() << ":" << sockets[s].getCode() << ";";
    }

    for(int g=0; g<gpios.size(); g++) {
        out << "gpio:" << gpios[g].getName() << ":" << Tools::convertIntToStr(gpios[g].getGpio()) << ";";
    }

    for(int s=0; s<schedules.size(); s++) {
        out << "schedule:" << schedules[s].getName() << ":" << schedules[s].getSocket() << ":" << schedules[s].getGpio() << ":" << Tools::convertIntToStr(schedules[s].getHour()) << ":" << Tools::convertIntToStr(schedules[s].getMinute()) << ":" << Tools::convertIntToStr(schedules[s].getOnoff()) << ":" << Tools::convertIntToStr(schedules[s].getStatus()) << ";";
    }

    out << "\x00" << endl;

    return out.str();
}

string executeCmd(string cmd) {
    if(cmd.length() < 1)
        return "statement too short";

    vector<string> words = Tools::explode(":", cmd);
    if(words.size() < 2)
        return "invalid statement";

    string action = words[0];
    string name = words[1];

    if (action == "list") {
        return generateList();
    } else if(action == "setsocket" && words.size() == 3) {
        for(int i=0; i<sockets.size(); i++) {
            if(sockets[i].getName()==name) {
                PiControl::send433Mhz(datagpio, sockets[i].getCode(), atoi(words[2].c_str()));
								syslog(LOG_INFO, "Set Socket %s to %d", name.c_str(), atoi(words[2].c_str()));
	    }
        }
    } else if(action == "addsocket" && words.size() == 3) {
        WSocket s(name, words[2]);
        sockets.push_back(s);
        saveSettings();
        loadSettings();
    } else if(action == "delsocket") {
        vector<WSocket>::iterator it = sockets.begin();
        while(it != sockets.end()) {
            if((*it).getName() == name) {
                it = sockets.erase(it);
            } else
                ++it;
        }
        saveSettings();
        loadSettings();
    } else if(action == "setgpio" && words.size() == 3) {
	for(int i=0; i<gpios.size(); i++) {
            if(gpios[i].getName()==name) {
		PiControl::writeGpio(gpios[i].getGpio(), atoi(words[2].c_str()));
		syslog(LOG_INFO, "Set Gpio %d to %d", gpios[i].getGpio(), atoi(words[2].c_str()));
	    }
	}
    } else if(action == "addgpio" && words.size() == 3) {
        Gpio g(name, atoi(words[2].c_str()));
        gpios.push_back(g);
        saveSettings();
        loadSettings();
    } else if(action == "delgpio") {
        vector<Gpio>::iterator it = gpios.begin();
        while(it != gpios.end()) {
            if((*it).getName() == name) {
                it = gpios.erase(it);
            } else
                ++it;
        }
        saveSettings();
        loadSettings();
		} else if(action == "setschedule" && words.size() == 2) {
			for(int s=0; s<schedules.size(); s++) {
				if(schedules[s].getName() == name) {
					if(schedules[s].getStatus())
						schedules[s].setStatus(0);
					else
						schedules[s].setStatus(1);
				}
			}
    } else if(action == "addschedule" && words.size() == 8) {
        Schedule s(name, words[2], words[3], atoi(words[4].c_str()), atoi(words[5].c_str()), atoi(words[6].c_str()), atoi(words[7].c_str()));
        schedules.push_back(s);
        saveSettings();
        loadSettings();
    } else if(action == "delschedule") {
        vector<Schedule>::iterator it = schedules.begin();
        while(it != schedules.end()) {
            if((*it).getName() == name) {
                it = schedules.erase(it);
            } else
                ++it;
        }
        saveSettings();
        loadSettings();
    }

    return "";
}

void *server(void *arg) {
    int sd, rc, n, cliLen;
    struct sockaddr_in cliAddr, servAddr;
    char msg[BUFLEN];

    sd=socket(AF_INET, SOCK_DGRAM, 0);
    if(sd<0) {
        syslog(LOG_CRIT, "Cant't open socket");
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
    rc = bind (sd, (struct sockaddr *) &servAddr,sizeof(servAddr));
    if(rc<0) {
        syslog(LOG_CRIT, "Can't bind socket to port %d", port);
        exit(1);
    }

    syslog(LOG_INFO, "Server listen on port %u", port);

    while(1) {
        memset(msg,0x0,BUFLEN);
        cliLen = sizeof(cliAddr);

        n = recvfrom(sd, msg, BUFLEN, 0, (struct sockaddr *) &cliAddr, (socklen_t*)&cliLen);

        if(n<0) {
            syslog(LOG_ERR, "Can't receive data");
        continue;
        }else {
            syslog(LOG_INFO, "Received: %s", msg);

						pthread_mutex_lock (&schedulesMutex);
						pthread_mutex_lock (&gpiosMutex);
						pthread_mutex_lock (&socketsMutex);

						// Parse and execute request
            string response = executeCmd(msg);

						pthread_mutex_unlock (&socketsMutex);
            pthread_mutex_unlock (&gpiosMutex);
            pthread_mutex_unlock (&schedulesMutex);

            int ns=sendto(sd,response.c_str(),strlen(response.c_str()),0,(struct sockaddr *)&cliAddr,cliLen);
            if(ns < 0 )
                syslog(LOG_ERR, "Can't send data");
            syslog(LOG_INFO, "Sent: %s", response.c_str());
        }
    }
    close(sd);
		pthread_exit(NULL);
}

void *scheduler(void *arg) {

	time_t now;
	struct tm now_info;

	while(1) {
		now = time(0);
		localtime_r(&now, &now_info);
		
		pthread_mutex_lock (&schedulesMutex);

		// Search for done, deleted and inactive Schedules
		vector<ScheduleTask>::iterator it = scheduleTasks.begin();
    while(it != scheduleTasks.end()) {
			int found = 0;
			int done = 0;
			int active = 1;

			for(int s=0; s < schedules.size(); s++) {
				if(schedules[s].getName() == (*it).getSchedule()) {
					found = 1;
					if(!schedules[s].getStatus())
						active = 0;
				}
			}

			if((*it).isDone()) {
				double deltaTime = difftime((*it).getTime(), now);
        if(deltaTime < -61)
					done = 1;
			}

			if(!found	|| !active || done) {
        syslog(LOG_INFO, "Removing Task '%s'", (*it).getSchedule().c_str());
				it = scheduleTasks.erase(it);
			}else
				++it;
		}

		// Add Schedules to Tasklist
		for(int s=0; s < schedules.size(); s++) {
			int found = 0;

			for(int st=0; st < scheduleTasks.size(); st++)
				if(schedules[s].getName()==scheduleTasks[st].getSchedule()) 
					found = 1;

			if(!found && schedules[s].getStatus()) {
				time_t newtime = time(0);
				struct tm tasktime;
				localtime_r(&newtime, &tasktime);   
        tasktime.tm_hour = schedules[s].getHour();
        tasktime.tm_min = schedules[s].getMinute();
        tasktime.tm_sec = 0;

				newtime = mktime(&tasktime);
        ScheduleTask task(schedules[s].getName(), newtime);
        scheduleTasks.push_back(task);
        syslog(LOG_INFO, "Adding Task '%s'", schedules[s].getName().c_str());
			} 
		}

		// Execute Tasks
		for(int st=0; st < scheduleTasks.size(); st++) {
			time_t tasktime = scheduleTasks[st].getTime();
			struct tm tasktime_info;
			localtime_r(&tasktime, &tasktime_info);

			string schedule = scheduleTasks[st].getSchedule();
		
			if(scheduleTasks[st].isDone() == 0 
				&& tasktime_info.tm_hour == now_info.tm_hour 
				&& tasktime_info.tm_min == now_info.tm_min) {
				
				syslog(LOG_INFO, "Executing Task '%s'", schedule.c_str());

				for(int s=0; s < schedules.size(); s++) {
					if(schedule == schedules[s].getName()) {
						if(schedules[s].getSocket() != "") {
							stringstream socket_out;
							socket_out << "setsocket:" << schedules[s].getSocket() << ":" << schedules[s].getOnoff();

							pthread_mutex_lock (&gpiosMutex);
            	pthread_mutex_lock (&socketsMutex);

							string response = executeCmd(socket_out.str());

            	pthread_mutex_unlock (&socketsMutex);
            	pthread_mutex_unlock (&gpiosMutex);
							
						}
				
						if(schedules[s].getGpio() != "") {
          		stringstream gpio_out;
          		gpio_out << "setgpio:" << schedules[s].getGpio() << ":" << schedules[s].getOnoff();

							pthread_mutex_lock (&gpiosMutex);
              pthread_mutex_lock (&socketsMutex);

              string response = executeCmd(gpio_out.str());

              pthread_mutex_unlock (&socketsMutex);
              pthread_mutex_unlock (&gpiosMutex);
						}
			    }  	
				}
				scheduleTasks[st].setDone(1);
			}
		}
		
		pthread_mutex_unlock (&schedulesMutex);	
		
		sleep(1);
	}

	pthread_exit(NULL);
}

int main(void)
{
  openlog("powerpi", LOG_PID|LOG_CONS, LOG_USER);

	time_t now = time(0);
	syslog(LOG_INFO, "Current Scheduler-Time: %s", ctime(&now));

  syslog(LOG_INFO, "Loading settings");
	loadSettings();

  pthread_t scheduleThread, serverThread;

	syslog(LOG_INFO, "Start server + scheduler");
	pthread_create(&serverThread, NULL, server, NULL);
	pthread_create(&scheduleThread, NULL, scheduler, NULL);

	pthread_join(serverThread, NULL);
	pthread_join(scheduleThread, NULL);

	pthread_mutex_destroy(&socketsMutex);
  pthread_mutex_destroy(&gpiosMutex);
  pthread_mutex_destroy(&schedulesMutex);

	closelog();
}
