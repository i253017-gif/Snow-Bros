#include<SFML/Graphics.hpp>
#include"platform.h"

Platform::Platform()
{
	shape.setSize(sf::Vector2f(0, 0));
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(0, 0);

	//ADD TEXTURES AND SPRITES WHEN READY
}
Platform::Platform(float x, float y, float width, float height)
{
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(x, y);

	//ADD TEXTURES AND SPRITES WHEN READY
}
void Platform::render(sf::RenderWindow& window)
{
	window.draw(shape);
	//window.draw(sprite);  when ready
}
sf::FloatRect Platform::getBounds()
{
	return shape.getGlobalBounds();
}
