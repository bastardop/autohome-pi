SOURCE = powerpi.cpp structs.cpp xmlreader.cpp tools.cpp picontrol.cpp -lwiringPi -lpthread
APP = xml.bin
CC = g++

all: $(APP)

$(APP): $(SOURCE)
	chmod -R 755 *
	$(CC) $(SOURCE) -o $(APP)

