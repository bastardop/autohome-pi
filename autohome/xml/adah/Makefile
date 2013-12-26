SOURCE = dht.cpp bina.cpp -lbcm2835 -lwiringPi -std=c++11
APP = bina
CC = g++-4.7

all: $(APP)

$(APP): $(SOURCE)
	chmod -R 755 *
	$(CC) $(SOURCE) -o $(APP)

