#include"snow_ball.h"
snow_ball::snow_ball(float x, float y, float vx, float vy) :Projectile(x, y, vx, vy, 1) {

	if (tex.loadFromFile("assets/snowball.png")) {
		visual.setTexture(tex);
	}

}
void snow_ball::draw(sf::RenderWindow& window) {
        visual.setPosition(pos_x, pos_y);
        window.draw(visual);
    }


//ABIHA ADD HOW THE BALL IS GONNA MOVE
void snow_ball::update(float delta_time) {
    
}

// ADD LOGIC FOR HOW SNOW WILL BE DEPOSITED ON ENEMY WHEN IT HITS IT
void snow_ball::on_hit() {
    
}

snow_ball::~snow_ball(){}