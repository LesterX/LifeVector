CC=g++
CFLAGS=-c
CMATH=-lm
PFLAG=-lmysqlclient
PFLAG2=-L/usr/include/curl/lib -lcurl
PFLAG3=-lcrypto

all: clean main 

main: UserControllerTest.o user.o UserLibrary.o hashfunc.o UserController.o Database.o DataDepositor.o md5.o RawDataRepository.o googleAPI.o SystemTimeManager.o CURLplusplus.o EncryptionModule.o ArchiveLocation.o ArchiveLibrary.o ArchiveTest.o CoordinateInformation.o LocationInformation.o UserVisitInfo.o VisitLog.o
	$(CC) -o $@ $^ $(CMATH) $(PFLAG) $(PFLAG2) $(PFLAG3)

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

googleAPI.cpp.o: googleAPI.cpp
	$(CC) $(CFLAGS) -o $@ $< 	

CURLplusplus.o: CURLplusplus.cpp
	$(CC) $(CFLAGS) -o $@ $< 	

EncryptionModule.o: EncryptionModule.cpp
	$(CC) $(CFLAGS) -o $@ $<

SystemTimeManager.o: SystemTimeManager.cpp
	$(CC) $(CFLAGS) -o $@ $<

ArchiveLocation.o: ArchiveLocation.cpp 
	$(CC) $(CFLAGS) -o $@ $<

ArchiveLibrary.o: ArchiveLibrary.cpp
	$(CC) $(CFLAGS) -o $@ $<

ArchiveTest.o: ArchiveTest.cpp
	$(CC) $(CFLAGS) -o $@ $<

CoordinateInformation.o: CoordinateInformation.cpp
	$(CC) $(CFLAGS) -o $@ $<

LocationInformation.o: LocationInformation.cpp
	$(CC) $(CFLAGS) -o $@ $<

UserVisitInfo.o: UserVisitInfo.cpp
	$(CC) $(CFLAGS) -o $@ $<

VisitLog.o: VisitLog.cpp
	$(CC) $(CFLAGS) -o $@ $<

test: clean main #cleans and runs main with the test file
	sudo ./main

clean:
	rm -f *.o main

