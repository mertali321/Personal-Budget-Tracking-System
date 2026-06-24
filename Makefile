all: program

program: main.o butce.o kayit.o
	g++ main.o butce.o kayit.o -o program.exe

main.o: main.cpp butce/butce.h
	g++ -c main.cpp

butce.o: butce/butce.cpp butce/butce.h kayit/kayit.h
	g++ -c butce/butce.cpp

kayit.o: kayit/kayit.cpp kayit/kayit.h
	g++ -c kayit/kayit.cpp

clean:
	del /Q /F *.o program.exe
