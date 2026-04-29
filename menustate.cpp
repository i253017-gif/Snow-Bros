#include<SFML/Graphics.hpp>
#include<iostream>
#include"menustate.h"

//include other state headers as well

menuState::menuState(stateMachine* m)
{
	machine = m;
}

void menuState::handleInput(inputManager& input)
{
	
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