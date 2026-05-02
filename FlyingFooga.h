#pragma once
#include "Botom.h"
#include<SFML/Graphics.hpp>
class FlyingFooga :public Botom {
protected:
	bool  flying;
	float fly_timer;
	sf::Sprite visual;
	sf::RectangleShape shape;
	sf::Texture text;

	bool isFlying;
	float flightTime;    //how long the flight is
	float groundTime;   //how long on ground beofre flying again
	float flightTimer;					//remove??
	float currentTime;  //to measure grounfTime and flightTime
	int directionX;
	int directionY;
	float flySpeed;
public:
	FlyingFooga(float x, float y, float speed_mult, int extra_hits);


	void draw(sf::RenderWindow& window) override;
	void move(float delta_time) override;
	void update(float time) override;
	sf::FloatRect getBounds() override;
	std::string get_type() const override;
	~FlyingFooga();

	//getter ND setters
	bool get_flying();
	float get_fly_timer();
	void set_flying(bool state);
	void set_fly_timer(float time);

	void enterFlight();
	void exitFlight();
};
