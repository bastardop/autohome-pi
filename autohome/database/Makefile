SOURCE = dbuse.cpp -lsqlite3 -lpthread
APP = ./dbuse
CC = gcc

all: $(APP)

$(APP): $(SOURCE)
	chmod -R 755 *
	$(CC) $(SOURCE) -o $(APP)

clean:
	rm -fv ./dbuse


install:

