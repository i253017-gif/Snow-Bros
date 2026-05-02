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
	player2Left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);   //left arrow
	player2Right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right); 
	player2Up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);  
	num1 = sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);  //singleplayer
	num2 = sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);

}

bool inputManager::isPlayer2LeftPressed()
{
	return player2Left;
}
bool inputManager::isPlayer2RightPressed()
{
	return player2Right;
}
bool inputManager::isPlayer2UpPressed()
{
	return player2Up;
}

bool inputManager::isNum1Pressed()
{
	return num1;
}
bool inputManager::isNum2Pressed()
{
	return num2;
}
