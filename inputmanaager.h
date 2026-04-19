#pragma once
#include <SFML/Graphics.hpp>
class inputManager
{
private:
	bool enter;
	bool escape;

public:
	bool getEnter();
	bool getEscape();
	void update();


	//will add motion detection for player later
};
