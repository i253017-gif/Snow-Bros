#include"FlyingFooga.h"
FlyingFooga::FlyingFooga(float x, float y, float speed_mult, int extra_hits) :Botom(x, y, speed_mult, extra_hits) {
    type = FLYING_FOOGA;
    shape.setSize(sf::Vector2f(25, 25));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);

    if (text.loadFromFile("assets/FlyingFooga_red.png")) {
        visual.setTexture(text);
        visual.setPosition(shape.getPosition());
    }

    //????/
    flying = false;
    fly_timer = 2.5f;

    isFlying = false;
    flightTime = 3.0f + (rand() % 5);
	groundTime = 4.0f + (rand() % 8);
    currentTime = 0.0f;
    directionX = (rand() % 3) - 1;     //-1,0,1
    directionY = (rand() % 3) - 1;
	flySpeed = 20.0f * speed_mult;

}

void FlyingFooga::draw(sf::RenderWindow& window) {

    window.draw(shape);
    window.draw(visual);


}

void FlyingFooga::move(float delta_time)
{
    if (isFlying)
    {
		shape.move(directionX * flySpeed * delta_time, directionY * flySpeed * delta_time);
        visual.setPosition(shape.getPosition());

        //bounds check again
        sf::FloatRect bounds = shape.getGlobalBounds();
        if (bounds.left < 0 || bounds.left + bounds.width > 700)
            directionX *= -1;
        if (bounds.top < 0 || bounds.top + bounds.height > 700)
            directionY *= -1;
    }
    else
		Botom::move(delta_time);

	currentTime += delta_time;
    if (isFlying)
    {
        if(currentTime>=flightTime)
			exitFlight();
    }
    else
        if (currentTime >= groundTime)
        {
            enterFlight();
        }
}

void FlyingFooga::enterFlight()
{
    isFlying = true;
    currentTime = 0.0f;    //reset
    velocityY = 0.0f;  //so gravity wont work on it and also overcomes the collision check for platforms

    directionX = (rand() % 3) - 1;     //-1,0,1
    directionY = (rand() % 3) - 1;

}

void FlyingFooga::exitFlight()
{
    isFlying = false;
    currentTime = 0.0f;    //reset
	velocityY = 0.0f;  //reset

}

void FlyingFooga::update(float time) 
{
    move(time);

    if (shape.getPosition().y >= 550)
    {
        shape.setPosition(shape.getPosition().x, 550);
        velocityY = 0.0f;
        isOnGround = true;
    }
}

FlyingFooga::~FlyingFooga() {}






//GETTERS AND SETTERS
void FlyingFooga::set_flying(bool state) {
    flying = state;
}
void FlyingFooga::set_fly_timer(float time) {
    fly_timer = time;

}

bool FlyingFooga::get_flying() {
    return flying;
}
float FlyingFooga::get_fly_timer() {
    return fly_timer;
}


sf::FloatRect FlyingFooga::getBounds() {
    return shape.getGlobalBounds();
}

std::string FlyingFooga::get_type() const 
{
    return "FlyingFooga";
}
