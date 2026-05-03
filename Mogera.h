#pragma once
#include"Boss.h"
class Mogera :public Boss {
private:
	float childSpwanTimer;
	float childCountDown;

	float platformTimer;
	float platformCountDown;
	bool isOnPlatform;
	float jumpTimer;
	float jumpCountDown;
	bool isTransparent;
	int gem_reward;//gems are rewarded on its defeat

	
public:
	Mogera(float x, float y, int hp);
	~Mogera();
	//gette and setters
	float get_child_timer();
	void set_child_timer(float time);
	int get_gem_reward();
	void set_gem_reward(int reward);

	void draw(sf::RenderWindow& window) override;
	void update(float delta_time) override;
	void move(float delta_time) override;
	sf::FloatRect getBounds() override;
	std::string get_type() const override;

	bool setTransparent();
	void setPhase();
	void setOnPlatform(bool platform);

	bool get_is_transparent();
	void set_is_transparent(bool transparent);

	float get_velocity();
	void set_velocity(float v);

	float get_child_count_down();
	void set_child_count_down(float time);

	float get_child_spawn_timer();
	void set_child_spawn_timer(float timer);
};