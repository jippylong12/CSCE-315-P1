# makefile

all: app database

app: Table.o Parser.o DBsystem.o App.o
	g++ -std=c++11  -o app Table.o Parser.o DBsystem.o App.o
	clear

App.o:	App.cpp
	g++ -c -std=c++11 App.cpp
	
DBsystem.o: DBsystem.cpp DBsystem.h App.cpp
	g++ -c -std=c++11 DBsystem.cpp DBsystem.h App.cpp
	

Table.o: Table.h Table.cpp
	g++ -c  -std=c++11 Table.h Table.cpp
	
Parser.o: Parser.h Parser.cpp Container.h
	g++ -c -std=c++11 Parser.h Parser.cpp Container.h

clean:
	rm *.o app
