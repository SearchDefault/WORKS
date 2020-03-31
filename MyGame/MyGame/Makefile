####MAKE FILE###

all: main.o person.o ##END LINKED##
	g++ content.o tile.o chunk.o world.o game.o person.o main.o -lsfml-graphics -lsfml-system -lsfml-window -o main

main.o: main.cpp ##BINARY FILE##
	g++ -c main.cpp

content.o: content.hpp content.cpp ##BINARY CLASS CONTENT##
	g++ -c content.cpp

game.o:	game.hpp game.cpp ##BINARY CLASS GAME##
	g++ game.cpp

world.o: world.hpp world.cpp ##BINARY CLASS WORLD##
	g++ -c world.cpp

chunk.o: chunk.hpp chunk.cpp ##BINARY CLASS CHUNK##
	g++ -c chunk.cpp

tile.o: tile.hpp tile.cpp ##BINARY CLASS TILE##
	g++ -c tile.cpp

person.o: person.hpp person.cpp ##BINARY CLASS PERSON##
	g++ -c person.cpp

clear: ##CLEAR DIR##
	rm -rf main.o content.o game.o world.o chunk.o tile.o person.o main