#include<SFML/Graphics.hpp>
#include"inputmanager.h"

bool inputManager::getEnter()
{
	return enter;
}
bool inputManager::getEscape()
{
	return escape;
}
void inputManager::update()
{
	enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter); //sfml handling ugh
	escape = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);


	//add motion later
}
