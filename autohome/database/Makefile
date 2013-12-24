SOURCE = sqdb.cpp dbuse.cpp -lsqlite3 -lpthread -ldl
APP = ./dbuse
CC = g++

all: $(APP)

$(APP): $(SOURCE)
#	chmod -R 755 *
	$(CC) $(SOURCE) -o $(APP)

clean:
	rm -fv ./dbuse


install:

