#include"Mogera.h"
Mogera::Mogera(float x, float y, int hp) :Boss(x, y, hp, hp) { //hits sem as hp
	shape.setSize(sf::Vector2f(50, 50));
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(x, y);
	
	if (text.loadFromFile("assets/Mogera.png"))
	{
		visual.setTexture(text);
		visual.setPosition(shape.getPosition());
	}
	gem_reward = 200;

	childSpwanTimer = 10.0f;
	childCountDown = 0.0f;
	platformCountDown = 0.0f;
	platformTimer = 15.0f;

	isTransparent = true;
	isOnPlatform = false;
	
	jumpCountDown = 0.0f;
	jumpTimer = 20.0f;
	velocityY = 0.0f;
}
void Mogera::draw(sf::RenderWindow& window) 
{
	//visual.setPosition(shape.getPosition());
	//window.draw(visual);
	window.draw(shape);
	show_health_bar(window);
}
void Mogera::move(float delta_time)
{
	// Apply gravity
	velocityY += 0.05f;  // gravity
	pos_y += velocityY;

	// Ground collision
	if (pos_y >= 550)
	{
		pos_y = 550;
		velocityY = 0;
		isOnGround = true;
		isOnPlatform = false;
	}
}
void Mogera::update(float delta_time)
{
	setPhase();

	childCountDown += delta_time;
	jumpCountDown += delta_time;
	if (jumpCountDown >= jumpTimer)
	{
		velocityY = -8.0f;
		jumpCountDown = 0.0f;
		isOnPlatform = false;
		isTransparent = false;
	}

	if (isOnPlatform)
	{
		platformCountDown += delta_time;
		if (platformCountDown >= platformTimer) 
		{
			isTransparent = true;  // Allow falling through
			platformCountDown = 0.0f;
		}
	}
	move(delta_time);
}

Mogera::~Mogera() {}

//setters and fetters

float Mogera::get_child_timer() {
	return childSpwanTimer;
}
int Mogera::get_gem_reward() {
	return gem_reward;
}
void Mogera::set_child_timer(float time) {
	childSpwanTimer = time;
}
void Mogera::set_gem_reward(int reward) {
	gem_reward = reward;
}

void Mogera::setPhase()
{
	float ratio = (float)hp / (float)boss_hp;

	if (ratio > 0.65f)
	{
		attack_phase = 1;
		childSpwanTimer = 10.0f;
	}
	else if (ratio > 0.35f)
	{
		attack_phase = 2;
		childSpwanTimer = 7.0f;
	}
	else
	{
		attack_phase = 3;
		childSpwanTimer = 4.0f;
	}
}

void Mogera::setOnPlatform(bool platform) {
	isOnPlatform = platform;
	if (platform) {
		isTransparent = false;  // Solid when on platform
		platformCountDown = 0.0f;
	}
}

sf::FloatRect Mogera::getBounds()
{
	return shape.getGlobalBounds();
}

bool Mogera::get_is_transparent() 
{
	return isTransparent;
}

void Mogera::set_is_transparent(bool transparent)
{
	isTransparent = transparent;
}

float Mogera::get_velocity()
{
	return velocityY;
}

void Mogera::set_velocity(float v)
{
	velocityY = v;
}

float Mogera::get_child_count_down()
{
	return childCountDown;
}

void Mogera::set_child_count_down(float time) 
{
	childCountDown = time;
}

float Mogera::get_child_spawn_timer()
{
	return childSpwanTimer;
}

void Mogera::set_child_spawn_timer(float time)
{
	childSpwanTimer = time;
}

std::string Mogera::get_type() const 
{
	return "Mogera";
}
