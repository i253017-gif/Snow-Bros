#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // ADD
class inputManager
{
private:
	bool enter;
	bool escape;
	bool left;
	bool right;
	bool up;
	bool space; //snowball

	bool player2Left;
	bool player2Right;
	bool player2Up;

	bool num1; //singleplayer
	bool num2; //multiplayer

	// ADD: audio (loaded once)
	sf::SoundBuffer clickBuffer;
	sf::Sound clickSound;

	// ADD: previous states (for "just pressed")
	bool prevEnter = false, prevEscape = false, prevLeft = false, prevRight = false, prevUp = false, prevSpace = false;
	bool prevP2Left = false, prevP2Right = false, prevP2Up = false;
	bool prevNum1 = false, prevNum2 = false;

public:
	inputManager();
	bool isEnterPressed();
	bool isEscapePressed();
	bool isLeftPressed();
	bool isRightPressed();
	bool isUpPressed();
	bool isSpacePressed();

	void update();


	bool isPlayer2LeftPressed();
	bool isPlayer2RightPressed();
	bool isPlayer2UpPressed();

	bool isNum1Pressed();
	bool isNum2Pressed();
};
