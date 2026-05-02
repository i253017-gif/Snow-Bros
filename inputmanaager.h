#pragma once
#include <SFML/Graphics.hpp>

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


public:
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
