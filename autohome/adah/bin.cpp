//
//  bin.cpp2
//  
//
//  Created by Christopher Täufert on 26.12.13.
//
//

//#include "dht.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <iostream>
#include <stdint.h>
#include <time.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include <vector>
#include <unistd.h>
//#include </home/pi/autohome-pi/autohome/database/sqdb.h>

using namespace std;

int MAXTIMINGS = 100;

int bits[250], data[100];
int bitidx = 0;

float f = 0;
float h = 0;
int type = 11;
int pin = 5;
vector<float> temp;

time_t new_time;

int main(void){
    
    if(wiringPiSetup()==-1) //setting wirinPi up
        exit(1);
    
    while(1){
        time(&new_time);
    cout << "start" << endl;
        int counter = 0;
        int laststate = HIGH;
        int j=0;
        bitidx = 0;
        back.clear();
        try {
            pinMode(pin,OUTPUT); //set gpio pin to OUTPUT
        }
        catch(...){ cout << "11" << endl;}
        digitalWrite(pin, HIGH);
        usleep(500000);  // wait 500 ms
        digitalWrite(pin, LOW);
        usleep(20000);   // wait 20 ms
        
        pinMode(pin, INPUT); // set gpio to INPUT
        data[0] = data[1] = data[2] = data[3] = data[4] = 0;
        
        // wait for pin to drop?
        while (digitalRead(pin) == 1) {
            usleep(1);
        }
        try {
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
        } catch(...) { return back;}
        if ((j >= 39) &&
            (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
            // found good data
            if (type == 11){
                try{
                    f = float(data[2]); //DHT11 is sending readable data
                    h = float(data[0]);}
                catch(...){
                    return back;
                }
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
        temp = back; //returning vector with data
        
        /*try {temp = readDHT(11, 5); //caling readDHT() from dht.cpp
        } catch(...){
            cout << "fehler beim auslesen" << endl;
        }*/
try {
    cout << "temp: " << temp[0] << "humi " << temp[1] << endl;
} catch(...){
cout << "obviusly wrong data" << endl;}     
/*
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
            sqdb::Exception excep(sqdb::Exception&);
            cout << "Fehler ist aufgetreten " << excep << endl;
        }

        this_thread::sleep_for (chrono::seconds(20));
 */
    }
}
