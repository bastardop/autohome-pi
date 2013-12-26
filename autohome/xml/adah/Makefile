SOURCE = dht.cpp -lbcm2835 -lwiringPi -std=c++11
APP = dht.bin
CC = g++

all: $(APP)

$(APP): $(SOURCE)
	chmod -R 755 *
	$(CC) $(SOURCE) -o $(APP)

