//
//  dht.cpp
//  
//
//  Created by Christopher Täufert on 26.12.13.
//
//  original from Adafruit_DHT_Drive C-File
//  changed that into C++-File and uses wiringPi instead of BCM2835

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <unistd.h>

using namespace std;
int MAXTIMINGS = 100;

int bits[250], data[100];
int bitidx = 0;

float f, h;

vector<float> back;

vector<float> readDHT(int type, int pin){
        int counter = 0;
        int laststate = HIGH;
        int j=0;
        back.clear();
    
        if(wiringPiSetup()==-1) //setting wirinPi up
        exit(1);

        pinMode(pin,OUTPUT); //set gpio pin to OUTPUT
        digitalWrite(pin, HIGH);
        usleep(500000);  // wait 500 ms
        digitalWrite(pin, LOW);
        usleep(20000);   // wait 200 ms
    
        pinMode(pin, INPUT); // set gpio to INPUT
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
            if (counter == 1000)
                break;
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
            // found good data
            if (type == 11){
                f = float(data[2]); //DHT11 is sending readable data
                h = float(data[0]);
            }
                
            if (type == 22) {
                
                h = data[0] * 256 + data[1]; //for DHT22 the recieved data need some additional chaning before output
                h /= 10;
                
                f = (data[2] & 0x7F)* 256 + data[3];
                f /= 10.0;
                if (data[2] & 0x80)  f *= -1;
                
            }
            back.push_back(f); //writing data into output
            back.push_back(h);
        }
    return back; //returning vector with data
}
