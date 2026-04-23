#include<SFML/Graphics.hpp>
#include<iostream>
#include"menustate.h"
#include"playstate.h"
//other states

playState::playState(stateMachine* m)
{
	machine = m;

	//nikal dena=====================================================================
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setString("PLAY STATE\nW = Jump | A/D = Move\nESC = Menu");
	text.setCharacterSize(20);
	text.setPosition(50, 20);
	//============================================================================
}
void playState::handleInput(inputManager& input)
{
	if (input.isEscapePressed())
		machine->changeState(new menuState(machine));
	//pressing esp while playing will take us to menu

	player.handleInput(input);
}
void playState::update()
{
	//actual game logic will come here
	//std::cout << "For testing! Entered play state update function\n";
	player.update();
}
void playState::render(sf::RenderWindow& window)
{
	//actual game rendering will come here
	//std::cout << "For testing! Entered play state render function\n";
	player.render(window);
	window.draw(text);
}
playState:: ~playState()
{
	// Empty is fine
}
