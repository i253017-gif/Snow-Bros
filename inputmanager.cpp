#include<SFML/Graphics.hpp>
#include"inputmanager.h"
inputManager::inputManager()
{
	// Put the file at this path relative to your working directory:
	// e.g. your exe folder/assets/click.wav
	clickBuffer.loadFromFile("audio/click.wav");
	clickSound.setBuffer(clickBuffer);
}
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



	// ADD: play click only on "new press" (not held every frame)
	bool justPressed =
		(enter && !prevEnter) ||
		(escape && !prevEscape) ||
		(left && !prevLeft) ||
		(right && !prevRight) ||
		(up && !prevUp) ||
		(space && !prevSpace) ||
		(player2Left && !prevP2Left) ||
		(player2Right && !prevP2Right) ||
		(player2Up && !prevP2Up) ||
		(num1 && !prevNum1) ||
		(num2 && !prevNum2);

	if (justPressed)
		clickSound.play();

	// ADD: update previous states for next frame
	prevEnter = enter; prevEscape = escape; prevLeft = left; prevRight = right; prevUp = up; prevSpace = space;
	prevP2Left = player2Left; prevP2Right = player2Right; prevP2Up = player2Up;
	prevNum1 = num1; prevNum2 = num2;





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
