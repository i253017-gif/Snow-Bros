#include<SFML/Graphics.hpp>
#include<iostream>
#include"menustate.h"
#include"playstate.h"
//include other state headers as well

menuState::menuState(stateMachine* m)
{
	machine = m;
}

void menuState::handleInput(inputManager& input)
{
	if (input.isEnterPressed())
		machine->changeState(new playState(machine)); //playstate on heap given machine as constructor
	                                                 //and used later as gamestate* bcs polymorphism
	//from menu pressing enter will take us to play state
	//will add other states here similarly like pause and stuff==============================
}

void menuState::update()
{
	//nothing to update in menu state for now
	std::cout << "For testing! Entered menu state update function\n";
}
void menuState::render(sf::RenderWindow& window)
{
	//nothing to render in menu state for now
	std::cout << "For testing! Entered menu state render function\n";
}
menuState::~menuState()
{
	// Empty is fine
}
