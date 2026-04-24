#include"Boss.h"
Boss::Boss(float x, float y, int hp, int hits) :Enemy(x, y, 0, hp, hits) {
	boss_hp = hp;
	attack_phase = 1;
}
//gwttes setters
int Boss::get_boss_hp() {
	return boss_hp;
}
int Boss::get_attack_phase() {
	return attack_phase;
}
void Boss::set_boss_hp(int hp) {
	boss_hp = hp;
}
void Boss::set_attack_phase(int a_p) {
	attack_phase = a_p;
}


void Boss::show_health_bar(sf::RenderWindow& window) {
	

    // background bar (gray)  
    sf::RectangleShape bg(sf::Vector2f(400, 20));
    bg.setPosition(200, 10);
    bg.setFillColor(sf::Color(100, 100, 100));
    window.draw(bg);

    // foreground bar (red) shrinks as hp drops
    float hp_ratio = (float)hp / (float)boss_hp;
    sf::RectangleShape bar(sf::Vector2f(400 * hp_ratio, 20));
    bar.setPosition(200, 10);
    bar.setFillColor(sf::Color::Red);
    window.draw(bar);






}





Boss::~Boss() {}