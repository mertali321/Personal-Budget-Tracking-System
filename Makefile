all: program

program: main.o butce.o
	g++ main.o butce.o -o program.exe


main.o: main.cpp butce/butce.h
	g++ -c main.cpp

butce.o: butce/butce.cpp butce/butce.h
	g++ -c butce/butce.cpp

clean:
	del /Q /F *.o program.exe