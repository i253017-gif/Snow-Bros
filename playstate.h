#pragma once
#include<SFML/Graphics.hpp>
#include"gamestate.h"
#include"statemachinee.h"
#include"player.h"
#include"snowball.h"
#include"platform.h"
#include"Botom.h"
#include"Enemy.h"
#include"Projectile.h"
#include"artillery_rocket.h"
#include"PowerUp.h"
#include"PowerUp_funcs.h"
#include"HUD_manager.h"
#include "Star.h" // ADDED

class playState : public gameState
{
private:
	stateMachine* machine;

	//=====================
	sf::Font font;
	sf::Text text;
	Player players[2];
	int playerCount;
	bool multiplayer;
	Snowball snowball[1000];
	int SBnum;
	bool wasSpacePressed;  //so only one snowball per key press
	Platform platform[100];
	int Pnum;
	Enemy* enemies[500];
	int Enum;
	artillery_rocket* projectile[500];
	int projectile_count;

	int lives;
	int score;

	int level;

	//next level
	float levelTransitionTimer = 0.0f;
	bool levelTransitioning = false;
	int nextLevel = 1;

	//================GEM RAIN 
	static const int MAX_GEMS = 100;
	float gemX[MAX_GEMS];
	float gemY[MAX_GEMS];
	float gemVelocity[MAX_GEMS];
	bool gemCollected[MAX_GEMS];
	int gemCount = 0;
	float cashTimer = 0.0f;
	bool isCashRain = false;

	HUD_manager hud;

	// ================= ADDED: POWER-UP SYSTEM =================
	static const int MAX_DROPS = 50;
	PowerUp_funcs* drops[MAX_DROPS];
	int dropCount;
	PowerUp_funcs* activePowerUp[2];  // Array for multiplayer

	// ================= ADDED: STAR EVENT =================
	StarEvent starEvent;
	int starLevel;
	bool wasMousePressed;

public:
	playState(stateMachine* m);
	void handleInput(inputManager& input);
	void update();
	void render(sf::RenderWindow& window);
	~playState();
	void loadLevel(int levelNum);

	int getScore();

	int getLevel();
	void setLevel(int lv);

	void spawnGemRain(int amount, bool isCash);
	void updateGems(float deltaTime);
	void checkGemCollisions();
	void renderGems(sf::RenderWindow& window);

	bool setMultiplayer(bool multiplayer);
};
