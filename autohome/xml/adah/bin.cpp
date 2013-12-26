//
//  dht.cpp
//  
//
//  Created by Christopher Täufert on 26.12.13.
//
//

#include "dht.h"

//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program
//  15-January-2012
//  Dom and Gert
//


// Access from ARM Running Linux

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <bcm2835.h>
#include <iostream>
#include <stdint.h>


using namespace std;




int main(void){
    //if (!bcm2835_init())
      //  return 1;
    
    cout << "start" << endl;
    //bcm2835_gpio_fsel(17, BCM2835_GPIO_FSEL_OUTP);
    readDHT(11, 0);
    cout << "temp: " << f << " humi: " << h << endl;
}