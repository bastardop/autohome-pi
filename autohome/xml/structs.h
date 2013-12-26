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
#include <ctime>
#include <cstring>
#include <iostream>

#include "tools.h"

/* ---------------------- Gpio ---------------------- */

#ifndef GPIO_H
#define GPIO_H

class Gpio {

	private:
		std::string name;
    int gpio;

	public:
		Gpio();
		Gpio(std::string, int);
		~Gpio();

		void setName(std::string);
		void setGpio(int);

		std::string getName();
		int getGpio();

		std::string toString();
};

#endif

/* ---------------------- Schedule ---------------------- */

#ifndef SCHEDULE_H
#define SCHEDULE_H

class Schedule {

  private:
    std::string name;
    std::string socket;
    std::string gpio;
    int hour;
    int minute;
    int onoff;
    int status;

  public:
    Schedule();
    Schedule(std::string, std::string, std::string, int, int, int, int);
    ~Schedule();

    void setName(std::string);
    void setSocket(std::string);
    void setGpio(std::string);
    void setHour(int);
    void setMinute(int);
    void setOnoff(int);
    void setStatus(int);

    std::string getName();
    std::string getSocket();
    std::string getGpio();
    int getHour();
    int getMinute();
    int getOnoff();
    int getStatus();

    std::string toString();
};

#endif

/* ---------------------- ScheduleTask ---------------------- */

#ifndef SCHEDULETASK_H
#define SCHEDULETASK_H

class ScheduleTask {
	
	private:
		std::string schedule;
		time_t time;
		int done;
		int active;

	public:
		ScheduleTask();
		ScheduleTask(std::string, time_t);

		void setSchedule(std::string);
		void setTime(time_t);
		void setDone(int);

		std::string getSchedule();
		time_t getTime();
		int isDone();

		std::string toString();
};

#endif

/* ---------------------- WSocket ---------------------- */

#ifndef WSOCKET_H
#define WSOCKET_H

class WSocket {

  private:
    std::string name;
    std::string code;

  public:
    WSocket();
    WSocket(std::string, std::string);
    ~WSocket();

    void setName(std::string);
    void setCode(std::string);

    std::string getName();
    std::string getCode();

    std::string toString();
};

#endif

/* -------------- DHT --------------------*/

#ifndef DHT_H
#define DHT_H

class Dht {
    
    private:
        std::string name;
        std::string type;
        std::string gpio;
    
    public:
        Dht();
        Dht(std::string, std::string, std::string);
        ~Dht();
    
    void setName(std::string);
    void setType(std::string);
    void setGpio(std::string);
    
    std::string getName();
    std::string getType();
    std::string getGpio();
};

#endif
