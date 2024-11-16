CC=g++
CFLAGS=-std=c++11 -g -Wall 

all: driver 

batterypack.o: batterypack.h Scene3D.h batterypack.cpp 
	$(CC) $(CFLAGS) -c batterypack.cpp

driver: batterypack.o Scene3D.h driver.cpp
	$(CC) $(CFLAGS) -o driver batterypack.o driver.cpp

clean:
	rm *.o *.exe *.stackdump driver 