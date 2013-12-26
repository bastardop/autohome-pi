//
//  dht.h
//  
//
//  Created by Christopher Täufert on 26.12.13.
//
//


#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <stdlib.h>
#include <sstream>

#ifndef ____dht__
#define ____dht__

class dhtread {
    
private:
    std::string content;
    std::vector<std::string> temps;
    void readDHT();
    
public:
    std::vector<std::string> getTemp();
    dhtread(std::string);
    ~dhtread();
    
};




#endif /* defined(____dht__) */
