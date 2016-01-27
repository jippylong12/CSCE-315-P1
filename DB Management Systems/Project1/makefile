# makefile

all: database

database: Table.o Parser.o DBsystem.o
	g++ -std=c++11  -o database Table.o Parser.o DBsystem.o


DBsystem.o: DBsystem.cpp
	g++ -c -std=c++11 DBsystem.cpp
	

Table.o: Table.h Table.cpp
	g++ -c  -std=c++11 Table.h Table.cpp
	
Parser.o: Parser.h Parser.cpp
	g++ -c -std=c++11 Parser.h Parser.cpp

clean:
	rm *.o database
