#pragma once
#include <SFML/Graphics.hpp>

class inputManager
{
private:
	bool enter;
	bool escape;

public:
	bool isEnterPressed();
	bool isEscapePressed();
	void update();


	//will add motion detection for player later
};
