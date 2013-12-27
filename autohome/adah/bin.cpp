//
//  bin.cpp
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

using namespace std;

vector<float> temp;

int main(void){
    cout << "start" << endl;
    temp = readDHT(11, 0); //caling readDHT() from dht.cpp
    cout << "temp: " << temp[0] << "humi " << temp[1] << endl;
}