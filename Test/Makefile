##MAKEFILE GAME##

##CONSTANT##
CC = g++
BINARY = Button.o EditorState.o MainMenuState.o Player.o HitboxComponent.o MovementComponent.o AnimationComponent.o entity.o state.o gamestate.o game.o main.o
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
##

all: $(BINARY) ##ALL PERPOSES##
	$(CC) $(BINARY) $(LIBS) -o main && ./main

main.o: main.cpp ##BINARY MAIN##
	$(CC) -c main.cpp

Button.o: Button.hpp Button.cpp ##BINARY BUTTON CLASS##
	$(CC) -c Button.cpp

EditorState.o: EditorState.hpp EditorState.cpp ##BINARY EDITOR STATE CLASS##
	$(CC) -c EditorState.cpp

MainMenuState.o: MainMenuState.hpp MainMenuState.cpp ##BINARY MAIN MENU STATE CLASS##
	$(CC) -c MainMenuState.cpp

HitboxComponent.o: HitboxComponent.hpp HitboxComponent.cpp ##BINARY HITBOXCOMPONENT CLASS##
	$(CC) -c HitboxComponent.cpp

MovementComponent.o: MovementComponent.hpp MovementComponent.cpp ##BINARY MOVEMENTCOMPONENT CLASS##
	$(CC) -c MovementComponent.cpp

AnimationComponent.o: AnimationComponent.hpp AnimationComponent.cpp  ##BINARY ANIMATIONCOMPONENT CLASS##
	$(CC) -c AnimationComponent.cpp

entity.o: entity.hpp entity.cpp ##BINARY ENTITY CLASS##
	$(CC) -c entity.cpp

Player.o: Player.hpp Player.cpp ##BINARY PLAYER CLASS##
	$(CC) -c Player.cpp

state.o: state.hpp state.cpp ##BINARY STATE CLASS##
	$(CC) -c state.cpp

gamestate.o: gamestate.hpp gamestate.cpp ##BINARY GAMESTATE CLASS##
	$(CC) -c gamestate.cpp

game.o: game.hpp game.cpp ##BINARY GAME CLASS##
	$(CC) -c game.cpp

run: ##RUN GAME##
	./main

clear: ##CLEAR BINARY FILES##
	rm -rf main *.o
