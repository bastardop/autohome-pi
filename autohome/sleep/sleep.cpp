#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <time.h>
#include <iostream>
#include <pthread.h>

using namespace std;

void *sleepa(void *arg) {
	time_t stamp;
	cout << "start 1 " << endl;
	while(1){
		time(&stamp);
		cout << "timestamp 1 " << stamp << endl;
		this_thread::sleep_for (chrono::seconds(10));
	}
}

void *sleepb(void *arg) {
	time_t stamp;
	cout << "start 2 " << endl;
        while(1){
 		this_thread::sleep_for (chrono::seconds(5));
		time(&stamp);
		cout << "timestamp 2 (wait 5) " << stamp << endl;
        }
}

int main(void){
	pthread_t sleepaThread, sleepbThread;

	pthread_create(&sleepaThread, NULL, sleepa, NULL);
	pthread_create(&sleepbThread, NULL, sleepb, NULL);

	pthread_join(sleepaThread, NULL);
	pthread_join(sleepbThread, NULL);

}
