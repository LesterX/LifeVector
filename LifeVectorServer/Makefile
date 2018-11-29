CC=g++
CFLAGS=-c
CXXFLAGS=$(CFLAGS)
CMATH=-lm
PFLAG=-lmysqlclient
PFLAG2=-L/usr/include/curl/lib -lcurl
PFLAG3=-lcrypto

all: clean main 

main: ./Test_Runners/UserControllerTest.o user.o UserLibrary.o hashfunc.o UserController.o Database.o DataDepositor.o md5.o RawDataRepository.o googleAPI.o placesAPI.o SystemTimeManager.o CURLplusplus.o EncryptionModule.o ArchivedLocation.o ArchiveLibrary.o CoordinateInformation.o LocationInformation.o UserVisitInfo.o VisitLog.o
	$(CC) -o $@ $^ $(CMATH) $(PFLAG) $(PFLAG2) $(PFLAG3)

TestArch: ./Test_Runners/ArchiveTest.o ArchiveLibrary.o ArchivedLocation.o LocationInformation.o CoordinateInformation.o UserVisitInfo.o VisitLog.o googleAPI.o placesAPI.o SystemTimeManager.o CURLplusplus.o user.o UserLibrary.o hashfunc.o UserController.o Database.o DataDepositor.o md5.o RawDataRepository.o
	$(CC) -o $@ $^ $(CMATH) $(PFLAG) $(PFLAG2) $(PFLAG3)

<<<<<<< HEAD
TestFetch: fetchTest.o fetchReport.o ArchiveLibrary.o ArchivedLocation.o LocationInformation.o CoordinateInformation.o UserVisitInfo.o VisitLog.o googleAPI.o placesAPI.o SystemTimeManager.o CURLplusplus.o user.o UserLibrary.o hashfunc.o UserController.o Database.o DataDepositor.o md5.o RawDataRepository.o
=======
TestFetch: ./Test_Runners/fetchTest.cpp fetchReport.o ArchiveLibrary.o ArchivedLocation.o LocationInformation.o CoordinateInformation.o UserVisitInfo.o VisitLog.o googleAPI.o placesAPI.o SystemTimeManager.o CURLplusplus.o user.o UserLibrary.o hashfunc.o UserController.o Database.o DataDepositor.o md5.o RawDataRepository.o
>>>>>>> bba0476cf89b8b5f766b0abfadb968ced1fb2168
	$(CC) -o $@ $^ $(CMATH) $(PFLAG) $(PFLAG2) $(PFLAG3)

ArchLib: ./Test_Runners/ALibTest.o ArchiveLibrary.o ArchivedLocation.o LocationInformation.o CoordinateInformation.o UserVisitInfo.o VisitLog.o user.o UserLibrary.o hashfunc.o UserController.o Database.o DataDepositor.o md5.o RawDataRepository.o googleAPI.o placesAPI.o SystemTimeManager.o CURLplusplus.o EncryptionModule.o
	$(CC) -o $@ $^ $(CMATH) $(PFLAG) $(PFLAG2) $(PFLAG3)

TestSquash: ./Test_Runners/TestSquash.o ArchiveLibrary.o ArchivedLocation.o LocationInformation.o CoordinateInformation.o UserVisitInfo.o VisitLog.o user.o UserController.o UserLibrary.o hashfunc.o Database.o DataDepositor.o md5.o RawDataRepository.o googleAPI.o placesAPI.o SystemTimeManager.o CURLplusplus.o squasher.o
	$(CC) -o $@ $^ $(CMATH) $(PFLAG) $(PFLAG2) $(PFLAG3)

TestSquash.o: ./Test_Runners/TestSquash.cpp
	$(CC) $(CFLAGS) -o $@ $<

ALibTest.o: ./Test_Runners/ALibTest.cpp
	$(CC) $(CFLAGS) -o $@ $<

fetchTest.o: ./Test_Runners/fetchTest.cpp
	$(CC) $(CFLAGS) -o $@ $<

fetchReport.o: fetchReport.cpp
	$(CC) $(CFLAGS) -o $@ $<

UserControllerTest.o: ./Test_Runners/UserControllerTest.cpp
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

squasher.o: squasher.cpp
	$(CC) $(CFLAGS) -o $@ $<

RawDataRepository.o: RawDataRepository.cpp
	$(CC) $(CFLAGS) -o $@ $<

googleAPI.cpp.o: googleAPI.cpp
	$(CC) $(CFLAGS) -o $@ $< 	

placesAPI.o: placesAPI.cpp
	$(CC) $(CFLAGS) -o $@ $< 	

CURLplusplus.o: CURLplusplus.cpp
	$(CC) $(CFLAGS) -o $@ $< 	

EncryptionModule.o: EncryptionModule.cpp
	$(CC) $(CFLAGS) -o $@ $<

SystemTimeManager.o: SystemTimeManager.cpp
	$(CC) $(CFLAGS) -o $@ $<

ArchiveTest.o: ./Test_Runners/ArchiveTest.cpp
	$(CC) $(CFLAGS) -o $@ $<

ArchivedLocation.o: ArchivedLocation.cpp 
	$(CC) $(CFLAGS) -o $@ $<

ArchiveLibrary.o: ArchiveLibrary.cpp
	$(CC) $(CFLAGS) -o $@ $<

CoordinateInformation.o: CoordinateInformation.cpp
	$(CC) $(CFLAGS) -o $@ $<

LocationInformation.o: LocationInformation.cpp
	$(CC) $(CFLAGS) -o $@ $<

UserVisitInfo.o: UserVisitInfo.cpp
	$(CC) $(CFLAGS) -o $@ $<

VisitLog.o: VisitLog.cpp
	$(CC) $(CFLAGS) -o $@ $<

ATest: TestArch
	@echo Running ArchiveTest
	./TestArch

ALibTest: ArchLib
	@echo Run ArchLib
	./ArchLib

testFetch: TestFetch
	./TestFetch

test: clean main #cleans and runs main with the test file
	sudo ./main

clean:
	rm -f *.o main TestArch ArchLib TestSquash


