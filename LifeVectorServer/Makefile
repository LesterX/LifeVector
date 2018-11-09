CC=g++
CFLAGS=-c
CMATH=-lm
PFLAG=-lmysqlclient

all: clean main 

main: UserControllerTest.o user.o UserLibrary.o hashfunc.o UserController.o Database.o DataDepositor.o md5.o RawDataRepository.o
	$(CC) -o $@ $^ $(CMATH) $(PFLAG)

UserControllerTest.o: UserControllerTest.cpp
	$(CC) $(CFLAGS) -o $@ $<

user.o: user.cpp
	$(CC) $(CFLAGS) -o $@ $<

UserLibrary.o: UserLibrary.cpp
	$(CC) $(CFLAGS) -o $@ $<

hashfunc.o: hashfunc.cpp
	$(CC) $(CFLAGS) -o $@ $<

UserController.o: UserController.cpp
	$(CC) $(CFLAGS) -o $@ $<

Database.o: Database.cpp
	$(CC) $(CFLAGS) -o $@ $<

DataDepositor.o: DataDepositor.cpp
	$(CC) $(CFLAGS) -o $@ $<

md5.o: md5.cpp
	$(CC) $(CFLAGS) -o $@ $<

RawDataRepository.o: RawDataRepository.cpp
	$(CC) $(CFLAGS) -o $@ $<


test: clean main #cleans and runs main with the test file
	sudo ./main

clean:
	rm -f *.o main
