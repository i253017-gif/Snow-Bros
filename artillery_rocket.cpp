#include"artillery_rocket.h"
#include<cmath>

artillery_rocket::artillery_rocket(float x, float y, float vx, float vy, float rad) :Projectile(x, y, vx, vy, 1)
{
	blast_radius = rad;
	shape.setSize(sf::Vector2f(15, 15));
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(x, y);
	if (text.loadFromFile("assets/artillery_rocket.png")) {
		visual.setTexture(text);
		visual.setPosition(shape.getPosition());
	}

	velocityX = vx;
	velocityY = vy;
	has_exploded = false;
	explosion_timer = 0.0f;
	explosion_duration = 0.3f;
}

void artillery_rocket::draw(sf::RenderWindow& window)
{
	//visual.setPosition(pos_x, pos_y);
	//window.draw(visual);
	window.draw(shape);

	if (has_exploded) {
		sf::CircleShape explosion_circle(blast_radius);
		explosion_circle.setPosition(pos_x - blast_radius, pos_y - blast_radius);
		explosion_circle.setFillColor(sf::Color(255, 165, 0, 100));
		explosion_circle.setOutlineColor(sf::Color::Red);
		explosion_circle.setOutlineThickness(2.0f);
		window.draw(explosion_circle);
	}
}

void artillery_rocket::move(float delta_time) {
	velocityY += 0.05f;

	pos_x += velocityX * delta_time;
	pos_y += velocityY * delta_time;
}

void artillery_rocket::update(float delta_time) {
	if (!has_exploded) {
		move(delta_time);
	}
	else {
		explosion_timer += delta_time;
		if (explosion_timer >= explosion_duration) {
			is_moving = false;
		}
	}
}

void artillery_rocket::on_hit() {
	has_exploded = true;
	explosion_timer = 0.0f;
	velocityX = 0.0f;
	velocityY = 0.0f;
}


float artillery_rocket::get_blast_radius() {
	return blast_radius;
}

void artillery_rocket::set_blast_radius(float rad) {
	blast_radius = rad;
}

bool artillery_rocket::get_has_exploded() {
	return has_exploded;
}

void artillery_rocket::set_has_exploded(bool exploded) {
	has_exploded = exploded;
	if (exploded) {
		explosion_timer = 0.0f;
	}
}

artillery_rocket::~artillery_rocket() {}

sf::FloatRect artillery_rocket::getBounds() {
	return shape.getGlobalBounds();
}