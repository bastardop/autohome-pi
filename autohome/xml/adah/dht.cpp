//
//  dht.cpp
//  
//
//  Created by Christopher Täufert on 26.12.13.
//
//

//#include "dht.h"

//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program
//  15-January-2012
//  Dom and Gert
//


#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <bcm2835.h>
#include <iostream>
#include <stdint.h>

int MAXTIMINGS = 100;

//#define DEBUG


int bits[250], data[100];
int bitidx = 0;

using namespace std;



void readDHT(int type, int pin){
        int counter = 0;
        int laststate = HIGH;
        int j=0;
        
        // Set GPIO pin to output
    if(wiringPiSetup()==-1)
        exit(1);

        //bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    pinMode(pin,OUTPUT);
        digitalWrite(pin, HIGH);
        usleep(500000);  // 500 ms
        digitalWrite(pin, LOW);
        usleep(20000);
        
        //bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
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
                //nanosleep(1);         // overclocking might change this?
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
        }
    
    }
