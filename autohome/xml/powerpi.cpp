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
vector<Dht> dht;

vector<ScheduleTask> scheduleTasks;


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
    dht.clear();

  string settings = readFile(settingsFile);
	XmlReader reader(settings);
	port = reader.getPort();
	datagpio = reader.getDatagpio();
	sockets = reader.getSockets();
	gpios = reader.getGpios();
	schedules = reader.getSchedules();
    dht = reader.getDHT();

	syslog(LOG_INFO, "Settings: %s", getSettings().c_str());
}

void saveSettings() {
    string xmldata = XmlReader::generateXml(port, datagpio, sockets, gpios, schedules, dht);
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



int main(void)
{
 

	time_t now = time(0);
	
	loadSettings();
    for(int s=0; s<dht.size(); s++) {
        cout << "dht:" << dht[s].getName() << ":" << dht[s].getType() << ":" <<dht[s].getGpio() <<";" << endl;
    }


}
