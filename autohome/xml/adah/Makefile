SOURCE = bin.cpp dht.cpp -lwiringPi
APP = bin.bin
CC = g++

all: $(APP)

$(APP): $(SOURCE)
	chmod -R 755 *
	$(CC) $(SOURCE) -o $(APP)

