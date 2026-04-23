#include<SFML/Graphics.hpp>
#include"inputmanager.h"

bool inputManager::isEnterPressed()
{
	return enter;
}
bool inputManager::isEscapePressed()
{
	return escape;
}
bool inputManager::isLeftPressed()
{
	return left;
}
bool inputManager::isRightPressed()
{
	return right;
}
bool inputManager::isUpPressed()
{
	return up;
}
bool inputManager::isSpacePressed()
{
	return space;
}
void inputManager::update()
{
	enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter); //sfml handling ugh
	escape = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);  //to menu
	left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space); //snowball

}
