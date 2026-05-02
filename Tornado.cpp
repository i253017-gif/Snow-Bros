#include"Tornado.h"
#include"knife.h"

Tornado::Tornado(float x, float y, float speed_mult, int extra_hits) :FlyingFooga(x, y, speed_mult, extra_hits)
{
	type = TORNADO;
	shape.setSize(sf::Vector2f(25, 25));
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(x, y);

	/*if (text.loadFromFile("assets/FlyingFooga_red.png"))
	{
		visual.setTexture(text);
		visual.setPosition(shape.getPosition());
	}*/

	knife_timer = 30.0f;
	currentTime = 0.0f;
	teleportTime = 30.0f + (rand() % 15);
	knifeNum = 0; 
}

void Tornado::draw(sf::RenderWindow& window) 
{
	window.draw(shape);
	window.draw(visual);

	// Drawing knives here bcs only tornado used knives
	for (int i = 0; i < knifeNum; i++)
		knives[i]->draw(window);
}

void Tornado::move(float delta_time) 
{
	FlyingFooga::move(delta_time);

	currentTime += delta_time;
	if (currentTime >= teleportTime) {
		Teleport();
		currentTime = 0.0f;
		teleportTime = 30.0f + (rand() % 15);
	}

	knife_timer -= delta_time;
	if (knife_timer <= 0.0f) 
	{
		if (knifeNum < 200) {
			knives[knifeNum++] = new knife(
				shape.getPosition().x,
				shape.getPosition().y,
				playerX,
				playerY
			);
		}
		knife_timer = 30.0f;   //timer reset
	}
	for (int i = 0; i < knifeNum; i++)
		knives[i]->update(delta_time);
}

void Tornado::update(float time)
{
	move(time); 

	if (shape.getPosition().y >= 550)
	{
		shape.setPosition(shape.getPosition().x, 550);
		velocityY = 0.0f;
		isOnGround = true;
	}
}

void Tornado::set_player_position(float x, float y)
{  
	playerX = x;
	playerY = y;
}

void Tornado::set_knife_timer(float time)
{
	knife_timer = time;
}

float Tornado::get_knife_timer()
{
	return knife_timer;
}

void Tornado::Teleport() 
{
	float randomX = rand() % 700;
	float randomY = rand() % 700;

	shape.setPosition(randomX, randomY);
	visual.setPosition(shape.getPosition());
}

Tornado::~Tornado()
{
	for (int i = 0; i < knifeNum; i++)
		delete knives[i];
}

std::string Tornado::get_type() const 
{
	return "Tornado";
}

sf::FloatRect Tornado::getBounds() {
	return shape.getGlobalBounds();
}
