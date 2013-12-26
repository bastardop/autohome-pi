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
#include <bcm2835.h>
#include <iostream>
#include <stdint.h>

using namespace std;

vector<float> temp;


int main(void){
    //if (!bcm2835_init())
      //  return 1;
    cout << "start" << endl;
    //bcm2835_gpio_fsel(17, BCM2835_GPIO_FSEL_OUTP);
    temp = readDHT(11, 0);
    cout << "temp: " << temp[0] << "humi " << temp[1] << endl;
}