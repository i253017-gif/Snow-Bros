#pragma once
#include<SFML/Graphics.hpp>

class Platform
{
private:
	sf::RectangleShape shape;
	sf::Sprite sprite;
	sf::Texture texture;

public:
	Platform();
	Platform(float x, float y, float width, float height);

	void render(sf::RenderWindow& window);
	sf::FloatRect getBounds();
};
