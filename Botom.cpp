#include"Botom.h"

Botom::Botom(float x, float y, float speed_mult, int extra_hits) :Enemy(x, y, 10.0f * speed_mult, 1, 1 + extra_hits) {
    
    shape.setSize(sf::Vector2f(25, 25));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
   
    /*if (text.loadFromFile("assets/botom_red.png")) {
        visual.setTexture(text);
        visual.setPosition(shape.getPosition());
    }*/
   
    velocityY = 0.0f;
    gravity = 0.05f;
    isOnGround = false;
    direction = (rand() % 2 == 0) ? 1 : -1;
    directionChange = 5.0f + (rand() % 14);
    directionTimer = 0.0f;

}

void Botom::draw(sf::RenderWindow& window) {

    window.draw(shape);
	window.draw(visual);


}

void Botom::move(float delta_time) 
{
   /*if (isFrozen())
        return;*/ 

    //horizontal motion
	shape.move(direction * speed * delta_time, 0);
	visual.setPosition(shape.getPosition());

	directionTimer += delta_time;
    if (directionTimer >= directionChange)
    {
        direction *= -1;
        directionTimer = 0;
		directionChange = 5.0f + (rand() % 14);
    }

    //y motion
    velocityY += gravity;
    shape.move(0, velocityY);
    visual.setPosition(shape.getPosition());

}
void Botom::update(float time) 
{
    move(time);

    if (shape.getPosition().y >= 550)
    {
        shape.setPosition(shape.getPosition().x, 550);
        velocityY = 0.0f;
        isOnGround = true;
    }
}

Botom::~Botom() {}





sf::FloatRect Botom::getBounds() {
    return shape.getGlobalBounds();
}

Botom::Botom() : Enemy(0, 0, 10.0f, 1, 1) {
    shape.setSize(sf::Vector2f(25, 25));
    shape.setFillColor(sf::Color::Red);
    if (text.loadFromFile("assets/botom_red.png")) {
        visual.setTexture(text);
        visual.setPosition(shape.getPosition());
    }
    velocityY = 0.0f;
    gravity = 0.05f;
    isOnGround = false;
    direction = (rand() % 2 == 0) ? 1 : -1;
    directionChange = 5.0f + (rand() % 14);
    directionTimer = 0.0f;
}

std::string Botom::get_type() const
{
    return "Botom";
}
