all:
#	gcc -Wall -pedantic -o receive_kw receive_kw.cpp -L/usr/local/lib -lwiringPi -lstdc++
	g++-4.7 -Wall -pedantic -o receive_kw ../database/sqdb.cpp receive_kw.cpp -L/usr/local/lib -lwiringPi -lsqlite3 -ldl -std=c++11

clean:
	rm -rf recieve_kw
