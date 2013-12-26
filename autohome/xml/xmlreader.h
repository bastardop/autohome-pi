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
#include <vector>
#include <iostream>
#include <typeinfo>
#include <stdlib.h>
#include <sstream>

#include "structs.h"
#include "tools.h"

#ifndef XMLREADER_H
#define XMLREADER_H

class XmlReader {

	private:
		std::string content;

		int port;
		int datagpio;
		std::vector<WSocket> sockets;
		std::vector<Gpio> gpios;
		std::vector<Schedule> schedules;


		std::string findTag(std::string);
		void parseSockets();
		void parseGpios();
		void parseSchedules();

	public:
		XmlReader(std::string);
		~XmlReader();

        static std::string generateXml(int, int, std::vector<WSocket>, std::vector<Gpio>, std::vector<Schedule>);
        std::string getContent();
		int getPort();
		int getDatagpio();
		std::vector<WSocket> getSockets();
		std::vector<Gpio> getGpios();
		std::vector<Schedule> getSchedules();
};

#endif
