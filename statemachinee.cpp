#include<SFML/Graphics.hpp>
#include"statemachinee.h"

stateMachine::stateMachine()
{
	currentState = nullptr;
}
void stateMachine::changeState(gameState* newState)
{
	if (currentState != nullptr)
		delete currentState;
	currentState = newState;
}
void stateMachine::handleInput(inputManager& input)
{
	if (currentState)
		currentState->handleInput(input); 
	//if current state is playstate then this means
	//playstate::handleInput will be called
}
void stateMachine::update() {
	if (currentState)
		currentState->update();
}

void stateMachine::render(sf::RenderWindow& window)
{
	if (currentState)
		currentState->render(window);
}
