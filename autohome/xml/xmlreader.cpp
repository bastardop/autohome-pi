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

#include "xmlreader.h"

/* ------------------- Public ------------------- */

XmlReader::XmlReader(std::string _content) {
	content = _content;
}

XmlReader::~XmlReader() {
}

std::string XmlReader::generateXml(int port, int datagpio, int senderon, int reciveron, int dhton, std::vector<WSocket> sockets, std::vector<Gpio> gpios, std::vector<Schedule> schedules, std::vector<Dht> dht) {
    std::stringstream xml;

    xml << "<port>" << Tools::convertIntToStr(port) << "</port>" << std::endl << std::endl;
    xml << "<datagpio>" << Tools::convertIntToStr(datagpio) << "</datagpio>" << std::endl << std::endl;
    xml << "<senderon>" << Tools::convertIntToStr(senderon) << "</senderon>" << std::endl << std::endl;
    xml << "<recieveron>" << Tools::convertIntToStr(recieveron) << "</recieveron>" << std::endl << std::endl;
    xml << "<dhton>" << Tools::convertIntToStr(dhton) << "</dhton>" << std::endl << std::endl;

    xml << "<dht>" << std::endl;
    for(int s=0; s<dht.size(); s++) {
        xml << dht[s].getName() << ":" << dht[s].getType() << ":" << dht[s].getGpio() << ";" << std::endl;
    }
    xml << "</dht>" << std::endl << std::endl;
    
    xml << "<sockets>" << std::endl;
    for(int s=0; s<sockets.size(); s++) {
        xml << sockets[s].getName() << ":" << sockets[s].getCode() << ";" << std::endl;
    }
    xml << "</sockets>" << std::endl << std::endl;

    xml << "<gpios>" << std::endl;
    for(int g=0; g<gpios.size(); g++) {
        xml << gpios[g].getName() << ":" << Tools::convertIntToStr(gpios[g].getGpio()) << ";" << std::endl;
    }
    xml << "</gpios>" << std::endl << std::endl;

    xml << "<schedules>" << std::endl;
    for(int s=0; s<schedules.size(); s++) {
        xml << schedules[s].getName() << ":" << schedules[s].getSocket() << ":" << schedules[s].getGpio() << ":" << Tools::convertIntToStr(schedules[s].getHour()) << ":" << Tools::convertIntToStr(schedules[s].getMinute()) << ":" << Tools::convertIntToStr(schedules[s].getOnoff()) << ":" << Tools::convertIntToStr(schedules[s].getStatus()) << ";" << std::endl;
    }
    xml << "</schedules>" << std::endl;

    return xml.str();
}

std::string XmlReader::getContent() {
    return content;
}

int XmlReader::getPort() {
	std::string port_str = findTag("port");
	return atoi(port_str.c_str());
}

int XmlReader::getDatagpio() {
    std::string datagpio_str = findTag("datagpio");
    return atoi(datagpio_str.c_str());
}

int XmlReader::getSenderon() {
    std::string senderon_str = findTag("senderon");
    return atoi(senderon_str.c_str());
}

int XmlReader::getRecieveron() {
    std::string reciveron_str = findTag("recieveron");
    return atoi(reciveron_str.c_str());
}

int XmlReader::getDhton() {
    std::string dhton_str = findTag("dhton");
    return atoi(dhton_str.c_str());
}

std::vector<WSocket> XmlReader::getSockets() {
	parseSockets();
	return sockets;
}

std::vector<Gpio> XmlReader::getGpios() {
	parseGpios();
	return gpios;
}

std::vector<Schedule> XmlReader::getSchedules() {
	parseSchedules();
	return schedules;
}

std::vector<Dht> XmlReader::getDHT() {
	parseDHT();
	return dht;
}

/* ------------------- Private ------------------ */

std::string XmlReader::findTag(std::string tag) {
	std::string tagContent;
	std::string openTag;
	std::string closeTag;

	openTag += std::string("<") + tag + std::string(">");
	closeTag += std::string("</") + tag + std::string(">");

	if(content.length() > 0 ) {
		int openTag_pos = content.find(openTag, 0);
		int closeTag_pos = content.find(closeTag, openTag_pos);

		if(openTag_pos < closeTag_pos) {
			tagContent = content.substr(openTag_pos + openTag.length(), closeTag_pos - (openTag_pos + openTag.length()) );
		}
	}
	return tagContent;
}

void XmlReader::parseSockets() {
	std::string entries = findTag("sockets");

	if(entries.length() > 0) {
		std::vector<std::string> lines = Tools::explode(";", entries);

		for(int l=0; l<lines.size(); l++) {
			if(lines[l].length() > 0) {
				std::vector<std::string> words = Tools::explode(":", lines[l]);
				WSocket s;
				for(int w=0; w<words.size(); w++) {
					if(typeid(words.at(0))==typeid(std::string))	s.setName(words[0]);
					if(typeid(words.at(1))==typeid(std::string))	s.setCode(words[1]);
				}
				sockets.push_back(s);
			}
		}
	}
}

void XmlReader::parseGpios() {
	std::string entries = findTag("gpios");

  if(entries.length() > 0) {
    std::vector<std::string> lines = Tools::explode(";", entries);

    for(int l=0; l<lines.size(); l++) {
      if(lines[l].length() > 0) {
        std::vector<std::string> words = Tools::explode(":", lines[l]);
        Gpio g;
        for(int w=0; w<words.size(); w++) {
          if(typeid(words.at(0))==typeid(std::string))  g.setName(words[0]);
          if(typeid(words.at(1))==typeid(std::string))  g.setGpio(atoi(words[1].c_str()));
        }
        gpios.push_back(g);
      }
    }
  }
}

void XmlReader::parseSchedules() {
	std::string entries = findTag("schedules");

  if(entries.length() > 0) {
    std::vector<std::string> lines = Tools::explode(";", entries);

    for(int l=0; l<lines.size(); l++) {
      if(lines[l].length() > 0) {
        std::vector<std::string> words = Tools::explode(":", lines[l]);
        Schedule s;
        for(int w=0; w<words.size(); w++) {
          if(typeid(words.at(0))==typeid(std::string))  s.setName(words[0]);
          if(typeid(words.at(1))==typeid(std::string))  s.setSocket(words[1]);
          if(typeid(words.at(2))==typeid(std::string))  s.setGpio(words[2]);
          if(typeid(words.at(3))==typeid(std::string))  s.setHour(atoi(words[3].c_str()));
          if(typeid(words.at(4))==typeid(std::string))  s.setMinute(atoi(words[4].c_str()));
          if(typeid(words.at(5))==typeid(std::string))  s.setOnoff(atoi(words[5].c_str()));
          if(typeid(words.at(6))==typeid(std::string))  s.setStatus(atoi(words[6].c_str()));
        }
        schedules.push_back(s);
      }
    }
  }
}

void XmlReader::parseDHT() {
	std::string entries = findTag("dht");
    
    if(entries.length() > 0) {
        std::vector<std::string> lines = Tools::explode(";", entries);
        
        for(int l=0; l<lines.size(); l++) {
            if(lines[l].length() > 0) {
                std::vector<std::string> words = Tools::explode(":", lines[l]);
                Dht d;
                for(int w=0; w<words.size(); w++) {
                    if(typeid(words.at(0))==typeid(std::string))  d.setName(words[0]);
                    if(typeid(words.at(1))==typeid(std::string))  d.setType(words[1]);
                    if(typeid(words.at(2))==typeid(std::string))  d.setGpio(words[2]);                }
                dht.push_back(d);
            }
        }
    }
}

