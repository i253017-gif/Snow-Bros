#include"Mogera_child.h"
Mogera_child::Mogera_child(float x, float y, float dx, float dy) :Enemy(x, y, 75.0f, 1, 1) {
	type = MOGERA_CHILD;
	shape.setSize(sf::Vector2f(30, 30));
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(x, y);
	if (text.loadFromFile("assets/mogera_child.png"))
	{
		visual.setTexture(text);
		visual.setPosition(shape.getPosition());
	}

	dir_x = dx;
	dir_y = dy;
	initialSpeed = 150.0f;  // Speed while being thrown
	isGravityOn = false;
	throwTimer = 0.0f;
	velocityY = 0.0f;

}

void Mogera_child::draw(sf::RenderWindow& window) {

	//visual.setPosition(pos_x, pos_y);
	//window.draw(visual);
	window.draw(shape);

}

void Mogera_child::move(float delta_time) 
{
	// First phase: thrown horizontally (no gravity)
	if (!isGravityOn)
	{
		throwTimer += delta_time;
		if (throwTimer >= THROW_DELAY) {
			isGravityOn = true;
		}
		// Move horizontally with initial speed
		pos_x += dir_x * initialSpeed * delta_time;
	}
	else {
		// Second phase: gravity applies, move and fall
		velocityY += 0.05f;  // Gravity
		pos_x += dir_x * initialSpeed * delta_time;
		pos_y += velocityY;
	}
}
void Mogera_child::update(float time) 
{
	move(time);

	// Ground collision
	if (pos_y >= 550) {
		pos_y = 550;
		velocityY = 0.0f;
		isOnGround = true;
	}
}

float  Mogera_child::get_dir_x() {
	return dir_x;

}
void  Mogera_child::set_dir_x(float x) {
	dir_x = x;
}
float Mogera_child::get_dir_y() {
	return dir_y;

}
void  Mogera_child::set_dir_y(float y) {

	dir_y = y;
}
Mogera_child::~Mogera_child() {}

sf::FloatRect Mogera_child::getBounds()
{
	return shape.getGlobalBounds();
}

std::string Mogera_child::get_type() const
{
	return "Mogera Child";
}
