//
//  dht.cpp
//  
//
//  Created by Christopher Täufert on 26.12.13.
//
//

#include "dht.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <iostream>
#include <stdint.h>
#include <unistd.h>

int MAXTIMINGS = 100;

int bits[250], data[100];
int bitidx = 0;
float f, h;

//using namespace std;

// --- public ------
dhtread::dhtread(std::string _content){
    content = _content;
}

dhtread::~dhtread(){
}

std::vector<std::string> dhtread::getTemp(){
    readDHT(11, 0);
    return temps;
}

// ----- private ---------

void dhtread::readDHT(int type, int pin){
        int counter = 0;
        int laststate = HIGH;
        int j=0;
    
    if(wiringPiSetup()==-1)
        exit(1);
    
        // Set GPIO pin to output
        pinMode(pin,OUTPUT);
        digitalWrite(pin, HIGH);
        usleep(500000);  // 500 ms
        digitalWrite(pin, LOW);
        usleep(20000);
    
        pinMode(pin, INPUT);
        data[0] = data[1] = data[2] = data[3] = data[4] = 0;
        
        // wait for pin to drop?
        while (digitalRead(pin) == 1) {
            usleep(1);
        }
        
        // read data!
        for (int i=0; i< MAXTIMINGS; i++) {
            counter = 0;
            while ( digitalRead(pin) == laststate) {
                counter++;
                if (counter == 1000)
                    break;
            }
            laststate = digitalRead(pin);
            if (counter == 1000) break;
            bits[bitidx++] = counter;
            
            if ((i>3) && (i%2 == 0)) {
                // shove each bit into the storage bytes
                data[j/8] <<= 1;
                if (counter > 200)
                    data[j/8] |= 1;
                j++;
            }
        }
    
        if ((j >= 39) &&
            (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
            // yay!
            if (type == 11){
                f = float(data[2]);
                h = float(data[0]);
            }
                
            if (type == 22) {
                
                h = data[0] * 256 + data[1];
                h /= 10;
                
                f = (data[2] & 0x7F)* 256 + data[3];
                f /= 10.0;
                if (data[2] & 0x80)  f *= -1;
                
            }
            temps.push_back(std::to_string(f));
            temps.push_back(std::to_string(h));
        }
    }
