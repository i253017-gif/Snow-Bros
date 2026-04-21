#pragma once
#include"Boss.h"
class Mogera :public Boss {
private :
	float child_timer; //how long does a child stays before the next is spawned
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








};
