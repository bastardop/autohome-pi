//
//  bin.cpp
//  
//
//  Created by Christopher Täufert on 26.12.13.
//
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <iostream>
#include <stdint.h>
#include <time.h>
#include <thread>
#include <chrono>

#include "dht.h"
#include "../database/sqdb.h"

using namespace std;

vector<float> temp;

time_t new_time;
int main(void){
    
    if(wiringPiSetup()==-1) //setting wirinPi up !!! darauf achten, dass im gesamten Projekt nur 1 wiringPiSetup laufen muss
        exit(1);
    
    while(1) {
        time(&new_time);
        cout << "start" << endl;
        //while (int i = 0; i < (menge an dhts)) {
            temp = readDHT(11, 0); //caling readDHT() from dht.cpp
            cout << "temp: " << temp[0] << "humi " << temp[1] << endl;
            if (temp[0] != 0){
                sqdb::Db db("/var/www/liteadmin/weather");
                try {
                    sqdb::Statement i = db.Query("insert into data (temp, humi, sender_id, time) values (?, ?, ?, ?)");
                    i.Bind(1, temp[0]);
                    i.Bind(2, temp[1]);
                    i.Bind(3, "999");
                    i.Bind(4, to_string(new_time));
                    i.Next();
                }
                catch ( const sqdb::Exception& e ){
                    cout << "Fehler ist in SQL aufgetreten " << endl;
                }
            // i++;
            }
        //}
        this_thread::sleep_for (chrono::seconds(20));
    }
}