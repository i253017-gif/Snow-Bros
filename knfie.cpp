#include"knife.h"



//calculates trajectory to player
knife::knife(float tornado_x, float tornado_y, float player_x, float player_y)
	:Projectile(tornado_x, tornado_y, 0, 0, 1) {

	shape.setSize(sf::Vector2f(10, 10));
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(tornado_x, tornado_y);

	if (text.loadFromFile("assets/knife.png"))
	{
		visual.setTexture(text);
		visual.setPosition(shape.getPosition());
	}
	is_active = true;

	//direction towards player
	float dx = player_x - tornado_x;
	float dy = player_y - tornado_y;
	float distance = std::sqrt(dx * dx + dy * dy);

	//vwlocity to player
	if (distance > 0) {
		vel_x = (dx / distance) * 150.0f;  
		vel_y = (dy / distance) * 150.0f;
	}
}

void knife::draw(sf::RenderWindow& window)
{
	shape.setPosition(pos_x, pos_y);  
	visual.setPosition(pos_x, pos_y);
	window.draw(shape);
	window.draw(visual);
}


void knife::update(float delta_time) 
{
	pos_x += vel_x * delta_time;
	pos_y += vel_y * delta_time;

	//deactivate again
	if (pos_x < -50 || pos_x > 750 || pos_y < -50 || pos_y > 750)
	{
		is_active = false;
	}

	
}


void knife::on_hit() {
	is_active = false;
}

bool knife::getIsActive() {
	return is_active;
}

void knife::setIsActive(bool state) {
	is_active = state;
}

knife::~knife() 
{

}