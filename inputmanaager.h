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

public:
	bool isEnterPressed();
	bool isEscapePressed();
	bool isLeftPressed();
	bool isRightPressed();
	bool isUpPressed();
	bool isSpacePressed();
	void update();

};
