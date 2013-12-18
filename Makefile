SOURCE = ./src/powerpi.cpp ./src/structs.cpp ./src/xmlreader.cpp ./src/tools.cpp ./src/picontrol.cpp -lwiringPi -lpthread
APP = ./bin/powerpi
CC = g++

all: $(APP)

$(APP): $(SOURCE)
	chmod -R 755 *
	$(CC) $(SOURCE) -o $(APP)

clean:
	rm -fv ./bin/*
	update-rc.d -f powerpi remove
	rm -fv /etc/init.d/powerpi
	rm -fv /bin/powerpi

install:
	cp ./src/settings /etc/default/powerpi
	cp ./bin/powerpi /bin/powerpi
	chmod 777 /etc/default/powerpi

	cp ./init/powerpi /etc/init.d
	update-rc.d powerpi defaults
