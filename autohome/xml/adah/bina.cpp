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

using namespace std;

vector<string> temps;
string temp;
string humi;

int main(void) {
    cout << "start" << endl;
    dhtread dht(dht);
    temps = dht.getTemp();
    cout << "temp " << temps[0] << " humi " << temps[1] << endl;
}