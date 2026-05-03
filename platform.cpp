#include<SFML/Graphics.hpp>
#include"platform.h"

Platform::Platform()
{
	shape.setSize(sf::Vector2f(0, 0));
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(0, 0);

	texture.loadFromFile("images/platform.png");
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);
}

Platform::Platform(float x, float y, float width, float height)
{
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(x, y);

	texture.loadFromFile("images/platform.png");
	sprite.setTexture(texture);

	sprite.setPosition(x, y);

	//scale sprite to match platform size
	if (texture.getSize().x != 0 && texture.getSize().y != 0)
	{
		sprite.setScale(
			width / texture.getSize().x,
			height / texture.getSize().y
		);
	}
}

void Platform::render(sf::RenderWindow& window)
{
	//window.draw(shape);
	window.draw(sprite);
}

sf::FloatRect Platform::getBounds()
{
	return shape.getGlobalBounds();
}