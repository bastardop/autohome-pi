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

#include "structs.h"

/* ---------------------- Gpio ---------------------- */

Gpio::Gpio() {
}

Gpio::Gpio(std::string _name, int _gpio) {
  name = _name;
  gpio = _gpio;
}

Gpio::~Gpio() {
}

void Gpio::setName(std::string _name) {
	name = _name;
}

void Gpio::setGpio(int _gpio) {
  gpio = _gpio;
}

std::string Gpio::getName() {
  return name;
}

int Gpio::getGpio() {
  return gpio;
}

std::string Gpio::toString() {
	std::string str = std::string("Gpio { name: ") + name + std::string("; gpio: ") + Tools::convertIntToStr(gpio) + std::string(" }");
	return str;
}

/* ---------------------- Schedule ---------------------- */

Schedule::Schedule() {
}

Schedule::Schedule(std::string _name, std::string _socket, std::string _gpio, int _hour, int _minute, int _onoff, int _status) {
    name = _name;
    socket = _socket;
    gpio = _gpio;
    hour = _hour;
    minute = _minute;
    onoff = _onoff;
    status = _status;
}

Schedule::~Schedule() {
}

void Schedule::setName(std::string _name) {
	name = _name;
}

void Schedule::setSocket(std::string _socket) {
	socket = _socket;
}

void Schedule::setGpio(std::string _gpio) {
	gpio = _gpio;
}

void Schedule::setHour(int _hour) {
	hour = _hour;
}

void Schedule::setMinute(int _minute) {
	minute = _minute;
}

void Schedule::setOnoff(int _onoff) {
	onoff = _onoff;
}

void Schedule::setStatus(int _status) {
	status = _status;
}

std::string Schedule::getName() {
  return name;
}

std::string Schedule::getSocket() {
  return socket;
}

std::string Schedule::getGpio() {
  return gpio;
}

int Schedule::getHour() {
  return hour;
}

int Schedule::getMinute() {
  return minute;
}

int Schedule::getOnoff() {
  return onoff;
}

int Schedule::getStatus() {
  return status;
}

std::string Schedule::toString() {
	std::string str = std::string("Schedule { name: ") + name + std::string("; socket: ") + socket + std::string("; gpio: ")
										+	gpio + std::string("; time: ") + Tools::convertIntToStr(hour) + std::string(":") + Tools::convertIntToStr(minute)
										+ std::string("; onoff: ") + Tools::convertIntToStr(onoff) + std::string("; status: ") + Tools::convertIntToStr(status) + std::string(" }");
	return str;
}

/* ---------------------- ScheduleTask ---------------------- */

ScheduleTask::ScheduleTask() {
	done = 0;
}

ScheduleTask::ScheduleTask(std::string _schedule, time_t _time) {
	schedule = _schedule;
	memcpy(&time, &_time, sizeof(time_t));
	done = 0;
}

void ScheduleTask::setSchedule(std::string _schedule) {
	schedule = _schedule;
}

void ScheduleTask::setTime(time_t _time) {
	time = _time;
}

void ScheduleTask::setDone(int _done) {
	done = _done;
}

std::string ScheduleTask::getSchedule() {
	return schedule;
}

time_t ScheduleTask::getTime() {
	return time;
}

int ScheduleTask::isDone() {
	return done;
}

std::string ScheduleTask::toString() {
  std::string str = std::string("ScheduleTask { name: ") + schedule + std::string("; time: ") + ctime(&time) + std::string("; done: ")
                    + Tools::convertIntToStr(done) + std::string(" }");
  return str;
}

/* ---------------------- WSocket ---------------------- */

WSocket::WSocket() {

}

WSocket::WSocket(std::string _name, std::string _code) {
  name = _name;
  code = _code;
}

WSocket::~WSocket() {
}

void WSocket::setName(std::string _name) {
	name = _name;
}

void WSocket::setCode(std::string _code) {
  code = _code;
}

std::string WSocket::getName() {
  return name;
}

std::string WSocket::getCode() {
  return code;
}

std::string WSocket::toString() {
	std::string str = std::string("WSocket { name: ") + name + std::string("; code: ") + code + std::string(" }");
	return str;
}

/* --------------- DHT ------------*/
DHT::DHT () {
    
}

DHT::DHT(std::string _name, std::string _type, std:string _gpio){
    name = _name;
    type = _type;
    gpio = _gpio;
}

DHT::~DHT() {
    
}

void DHT::setName(std::string _name){
    name = _name;
}

void DHT::setType(std::string _type){
    type = _type;
}

void DHT::setGpio(std::string _gpio){
    gpio = _gpio;
}

std:string DHT::getName(){
    return name;
}

std::string DHT::getType(){
    return type;
}

std::string DHT::getGpio(){
    return gpio;
}