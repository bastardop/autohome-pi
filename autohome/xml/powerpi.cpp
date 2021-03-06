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
string databaseFile;

int port;
int datagpio;
int senderon;
int recieveron;
int dhton;
int recievergpio;
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
    out << "Reciever-Gpio: " << recievergpio;
    out << "Sender On: " << senderon;
    out << "Reciever On: " << recieveron;
    out << "DHT On: " << dhton;
    out << "Datebase File: " << databaseFile;

	for(int s=0; s<sockets.size(); s++)
        out << sockets[s].toString();

	for(int g=0; g<gpios.size(); g++)
        out << gpios[g].toString();

	for(int s=0; s<schedules.size(); s++)
        out << schedules[s].toString();
    
    for(int d=0; d<dht.size(); d++) {
        out << dht[d].toString();
    }

    return out.str();
}

void loadSettings() {
    port = 9999;
    datagpio = 0;
    recievergpio = 0;
    dhton = 0;
    senderon = 0;
    recieveron = 0;
	sockets.clear();
	gpios.clear();
	schedules.clear();
    dht.clear();
    databaseFile = "";

  string settings = readFile(settingsFile);
	XmlReader reader(settings);
	port = reader.getPort();
	datagpio = reader.getDatagpio();
    dhton = reader.getDhton();
    recievergpio = reader.getRecievergpio();
    recieveron = reader.getRecieveron();
    senderon = reader.getSenderon();
    databaseFile = reader.getDatabase();
	sockets = reader.getSockets();
	gpios = reader.getGpios();
	schedules = reader.getSchedules();
    dht = reader.getDHT();

	syslog(LOG_INFO, "Settings: %s", getSettings().c_str());
}

void saveSettings() {
    string xmldata = XmlReader::generateXml(port, datagpio, recievergpio, senderon, recieveron, dhton, databaseFile, sockets, gpios, schedules, dht);
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

    for(int d=0; d<dht.size(); d++) {
        out << "dht:" << dht[d].getName() << ":" << dht[d].getType() << ":" << dht[d].getGpio() << ";";
    }

    out << "\x00" << endl;

    return out.str();
}



int main(void)
{
 

	time_t now = time(0);
	
	loadSettings();
    
    cout << "Datebase File: " << databaseFile << endl;
    
    if (dhton == 1) {
        
    
    for(int s=0; s<dht.size(); s++) {
        cout << "dht:" << dht[s].getName() << ":" << dht[s].getType() << ":" <<dht[s].getGpio() <<";" << endl;
    }
    } else
    {
        cout << "dht off" << endl;
    }

}
