#pragma once
#include"Enemy.h"


//MAKING AN ABSTRAT CLASS FOR ALL THE BOSS ENEMIES
//ALL THE BOSS INHERIT FROM THIS AND THIS INHERITS FROM ENEMY
//WE ARE MAKING THIS CZ BOSSES HAVE SOME FIMILAR FEATURES





class Boss :public Enemy {
protected:
	int boss_hp, attack_phase;
	/*boss hp is basically he max hp of boss which is diff than other enemies
	and attack phase is the current level of how boss attacks as it changed as
	hp drops*/

public:
	Boss(float x, float y, int hp, int hits);

	//ALL THESE PURE VIRTUAL CZ WE WONT CALL THIS DIRECTLY
	//WE WILL CALL CHILD CLASSES WHICH WILL OVERRIDE THESE

	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void move(float delta_time) = 0;
	virtual void update(float time) = 0;
	sf::FloatRect getBounds() = 0;


	//non virtual cz all bosses have sem exact health bars

	void show_health_bar(sf::RenderWindow& window);

	//getters and setter
	int get_boss_hp();
	int get_attack_phase();
	void set_boss_hp(int hp);
	void set_attack_phase(int phase);

	virtual~Boss();




};