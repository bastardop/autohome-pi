// this_thread::sleep_for example
#include <iostream>       // std::cout
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <time.h> 

using namespace std;
int main() 
{
time_t stamp;
cout << "start " << endl;
	while(1){
time(&stamp);  
cout << "timesatmpe " << stamp << endl;

    this_thread::sleep_for (chrono::seconds(10));
  
	}
}
