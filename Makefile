all: program

program: main.o butce.o
	g++ main.o butce.o -o program.exe

main.o: main.cpp kayit/butce.h
	g++ -I./kayit -c main.cpp

butce.o: kayit/butce.cpp kayit/butce.h
	g++ -I./kayit -c kayit/butce.cpp


clean:
	del /Q /F *.o program.exe