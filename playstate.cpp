#include<SFML/Graphics.hpp>
#include<iostream>
#include"menustate.h"
#include"playstate.h"
//other states

playState::playState(stateMachine* m)
{
	machine = m;
}
void playState::handleInput(inputManager& input)
{
	if (input.isEscapePressed())
		machine->changeState(new menuState(machine));
	//pressing esp while playing will take us to menu

	//other states
}
void playState::update()
{
	//actual game logic will come here
	std::cout << "For testing! Entered play state update function\n";
}
void playState::render(sf::RenderWindow& window)
{
	//actual game rendering will come here
	std::cout << "For testing! Entered play state render function\n";
}
