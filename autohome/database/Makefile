SOURCE = ./dbuse.cpp ./Database.cpp -lwiringPi -lpthread
APP = ./dbuse
CC = g++

all: $(APP)

$(APP): $(SOURCE)
	chmod -R 755 *
	$(CC) $(SOURCE) -o $(APP)

clean:
	rm -fv ./dbuse


install:

