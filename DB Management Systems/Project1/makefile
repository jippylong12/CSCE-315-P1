# makefile

all: database

database: Table.o Parser.o DBsystem.o main.o
	g++ -std=c++11  -o database Table.o Parser.o DBsystem.o main.o
	clear

main.o:	main.cpp
	g++ -c -std=c++11 main.cpp
	
DBsystem.o: DBsystem.cpp DBsystem.h main.cpp
	g++ -c -std=c++11 DBsystem.cpp DBsystem.h main.cpp
	

Table.o: Table.h Table.cpp
	g++ -c  -std=c++11 Table.h Table.cpp
	
Parser.o: Parser.h Parser.cpp
	g++ -c -std=c++11 Parser.h Parser.cpp

clean:
	rm *.o database
