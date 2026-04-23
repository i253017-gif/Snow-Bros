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

public:
	bool isEnterPressed();
	bool isEscapePressed();
	bool isLeftPressed();
	bool isRightPressed();
	bool isUpPressed();
	void update();

};
