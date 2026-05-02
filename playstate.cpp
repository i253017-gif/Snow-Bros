#include<SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include"menustate.h"
#include"playstate.h"
#include"snowball.h"
#include"player.h"
#include"FlyingFooga.h"
#include"Tornado.h"
#include"Mogera.h"
#include"Mogera_child.h"
#include"Gamachiki.h"
#include"artillery_rocket.h"
#include"Projectile.h"
#include"PowerUp.h"
#include"PowerUp_funcs.h"

//other states

playState::playState(stateMachine* m)
{
	machine = m;
	SBnum = 0;
	wasSpacePressed = false;
	Pnum = 0;
	Enum = 0;
	projectile_count = 0;;
	wasMousePressed = false;

	lives = 15;
	score = 0;
	srand(time(0));

	// ADDED: power-up system init
	dropCount = 0;
	for (int p = 0; p < 2; p++)
		activePowerUp[p] = nullptr;

	// ADDED: init level properly + choose star level once per playthrough
	level = 1;
	starLevel = 1 + (rand() % 10);

	playerCount = 1;
	multiplayer = false;

	loadLevel(level);
}

void playState::loadLevel(int levelNum)
{
	// ADDED: clear old drops (new level)
	for (int i = 0; i < dropCount; i++)
		delete drops[i];
	dropCount = 0;

	// ADDED: expire any active power-up at level end
	for (int p = 0; p < playerCount; p++)
	{
		if (activePowerUp[p])
		{
			activePowerUp[p]->expire(players[p]);
			delete activePowerUp[p];
			activePowerUp[p] = nullptr;
		}
	}

	Enum = 0;
	Pnum = 0;
	SBnum = 0;
	projectile_count = 0;
	levelTransitioning = false;
	levelTransitionTimer = 0.0f;

	// ADDED: spawn star only on chosen level
	if (levelNum == starLevel)
	{
		starEvent.spawn_star(350, 250);
	}

	if (levelNum == 1)
	{
		platform[Pnum++] = Platform(0, 100, 350, 30);
		platform[Pnum++] = Platform(0, 300, 200, 30);
		platform[Pnum++] = Platform(400, 300, 200, 30);
		platform[Pnum++] = Platform(140, 480, 370, 30);

		enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
		enemies[Enum++] = new Botom(400, 200, 1.2f, 0);
		enemies[Enum++] = new Botom(200, 250, 0.8f, 1);
	}
	else if (levelNum == 2)
	{
		platform[Pnum++] = Platform(0, 600, 700, 30);      // Bottom
		platform[Pnum++] = Platform(0, 400, 150, 30);      // Left
		platform[Pnum++] = Platform(275, 400, 150, 30);    // Center
		platform[Pnum++] = Platform(550, 400, 150, 30);    // Right
		platform[Pnum++] = Platform(150, 200, 150, 30);    // Upper left
		platform[Pnum++] = Platform(400, 200, 150, 30);    // Upper right

		enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
	}
	else if (levelNum == 3)
	{
		platform[Pnum++] = Platform(0, 600, 700, 30);      // Bottom
		platform[Pnum++] = Platform(0, 500, 120, 30);      // Left column 1
		platform[Pnum++] = Platform(150, 500, 120, 30);    // Left column 2
		platform[Pnum++] = Platform(290, 450, 120, 30);    // Center
		platform[Pnum++] = Platform(430, 500, 120, 30);    // Right column 1
		platform[Pnum++] = Platform(580, 500, 120, 30);    // Right column 2
		std::cout << "Level 3 loaded with " << Pnum << " platforms and " << Enum << " enemies.\n";
		enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
		std::cout << "enemy loaded";
	}
	else if (levelNum == 4)
	{
		platform[Pnum++] = Platform(0, 600, 700, 30);      // Bottom
		platform[Pnum++] = Platform(50, 350, 200, 30);     // Left
		platform[Pnum++] = Platform(250, 400, 200, 30);    // Center-left
		platform[Pnum++] = Platform(450, 400, 200, 30);    // Center-right
		platform[Pnum++] = Platform(600, 350, 100, 30);    // Right
		enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
	}
	else if (levelNum == 5)
	{
		platform[Pnum++] = Platform(0, 600, 700, 30);      // Bottom
		platform[Pnum++] = Platform(100, 400, 150, 30);    // Left platform
		platform[Pnum++] = Platform(450, 400, 150, 30);    // Right platform
		enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
	}
	else if (levelNum == 6)
	{
		platform[Pnum++] = Platform(0, 600, 700, 30);      // Bottom
		platform[Pnum++] = Platform(50, 480, 130, 30);     // Left step 1
		platform[Pnum++] = Platform(200, 380, 130, 30);    // Left step 2
		platform[Pnum++] = Platform(350, 280, 130, 30);    // Center
		platform[Pnum++] = Platform(500, 380, 130, 30);    // Right step 2
		platform[Pnum++] = Platform(620, 480, 80, 30);     // Right step 1
		enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
	}
	else if (levelNum == 7)
	{
		platform[Pnum++] = Platform(0, 600, 700, 30);      // Bottom
		platform[Pnum++] = Platform(100, 450, 150, 30);    // Left
		platform[Pnum++] = Platform(275, 350, 150, 30);    // Center
		platform[Pnum++] = Platform(450, 450, 150, 30);    // Right
		platform[Pnum++] = Platform(200, 200, 300, 30);    // Top platform
		enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
	}
	else if (levelNum == 8)
	{
		platform[Pnum++] = Platform(0, 600, 700, 30);      // Bottom
		platform[Pnum++] = Platform(50, 500, 100, 30);     // Left lower
		platform[Pnum++] = Platform(150, 400, 100, 30);    // Left middle
		platform[Pnum++] = Platform(275, 300, 150, 30);    // Center
		platform[Pnum++] = Platform(500, 400, 100, 30);    // Right middle
		platform[Pnum++] = Platform(600, 500, 100, 30);    // Right lower
		enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
	}
	else if (levelNum == 9)
	{
		platform[Pnum++] = Platform(0, 600, 700, 30);      // Bottom
		platform[Pnum++] = Platform(75, 450, 120, 30);     // Left
		platform[Pnum++] = Platform(290, 400, 120, 30);    // Center-left
		platform[Pnum++] = Platform(510, 400, 120, 30);    // Center-right
		platform[Pnum++] = Platform(600, 450, 100, 30);    // Right
		enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
	}
	else if (levelNum == 10)
	{
		platform[Pnum++] = Platform(0, 600, 700, 30);      // Bottom
		platform[Pnum++] = Platform(100, 400, 150, 30);    // Left platform
		platform[Pnum++] = Platform(450, 400, 150, 30);    // Right platform
		enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
	}
}

void playState::handleInput(inputManager& input)
{
	// ADDED: freeze gameplay input while choosing star power-up
	if (starEvent.get_showing_types())
		return;

	if (input.isEscapePressed())
		machine->changeState(new menuState(machine));


	for (int p = 0; p < playerCount; p++)
		players[p].handleInput(input, p);

	if (input.isSpacePressed() && SBnum < 100 && !wasSpacePressed)
	{
		for (int p = 0; p < playerCount; p++)
		{
			float startX = players[p].getBounds().left;
			if (players[p].getFacingDirection() == 1)
				startX += players[p].getBounds().width;
			float startY = players[p].getBounds().top + players[p].getBounds().height / 2;
			snowball[SBnum] = Snowball(startX, startY, players[p].getFacingDirection(), 5.0f, 500.0f);
			SBnum++;
		}
		wasSpacePressed = true;
	}
	else if (!input.isSpacePressed())
	{
		wasSpacePressed = false;  // Space released, ready for next press
	}

	// ===== PLATFORM COLLISIONS FOR ALL PLAYERS =====
	for (int p = 0; p < playerCount; p++)
	{
		players[p].setOnGround(false);  // Reset

		for (int i = 0; i < Pnum; i++)
		{
			sf::FloatRect playerBounds = players[p].getBounds();
			sf::FloatRect platformBounds = platform[i].getBounds();

			if (playerBounds.intersects(platformBounds))
			{
				if (players[p].getVelocity() > 0)
				{
					players[p].newPosition(playerBounds.left,
						platformBounds.top - playerBounds.height);
					players[p].setVelocity(0);
					players[p].setOnGround(true);
				}
			}
		}

		// ===== SCREEN BOUNDARIES FOR PLAYER =====
		sf::FloatRect playerBounds = players[p].getBounds();

		// Left boundary
		if (playerBounds.left < 0)
			players[p].newPosition(0, playerBounds.top);

		// Right boundary
		if (playerBounds.left + playerBounds.width > 700)
			players[p].newPosition(700 - playerBounds.width, playerBounds.top);

		// Bottom boundary - just push player back up
		if (playerBounds.top > 700)
			players[p].newPosition(playerBounds.left, 700 - playerBounds.height);

		// ===== PLAYER AND ENEMY COLLISIONS =====
		if (!players[p].isInvincible())
		{
			sf::FloatRect playerBounds = players[p].getBounds();
			for (int i = 0; i < Enum; i++)
			{
				sf::FloatRect enemyBounds = enemies[i]->getBounds();
				if (playerBounds.intersects(enemyBounds))
				{
					// ADDED: balloon mode grants immunity against ground enemies (Botom)
					if (players[p].isBalloonModeActive())
					{
						Botom* botom = dynamic_cast<Botom*>(enemies[i]);
						if (botom != nullptr)
							continue;  // immune to Botom while balloon mode active
					}
					players[p].loseLive();
					break; // Only lose one life per frame, even if colliding with multiple enemies
				}
			}
			if (players[p].getLives() <= 0)
			{
				//ADD GAME OVER SCREEN AND SHIT
				//FOR NOW END GAME
				machine->changeState(new menuState(machine));
			}
		}
	}


	//=====================================================================
	// ENEMY AND PLATFORM COLLISIONS
	for (int e = 0; e < Enum; e++)
	{
		enemies[e]->setOnGround(false);

		// Check platform collisions
		sf::FloatRect enemyBounds = enemies[e]->getBounds();
		for (int i = 0; i < Pnum; i++)
		{
			sf::FloatRect platformBounds = platform[i].getBounds();

			if (enemyBounds.intersects(platformBounds))
			{
				if (enemies[e]->getVelocity() > 0)
				{
					enemies[e]->newPosition(enemyBounds.left,
						platformBounds.top - enemyBounds.height);
					enemies[e]->setVelocity(0);
					enemies[e]->setOnGround(true);
				}
			}
		}

		// ENEMY AND SCREEN BOUNDARY
		if (enemyBounds.top > 700) {
			enemies[e]->newPosition(enemyBounds.left, 700 - enemyBounds.height);
			enemies[e]->setVelocity(0);
			enemies[e]->setOnGround(true);
		}

		// Left boundary
		if (enemyBounds.left < 0)
			enemies[e]->newPosition(0, enemyBounds.top);

		// Right boundary
		if (enemyBounds.left + enemyBounds.width > 700)
			enemies[e]->newPosition(700 - enemyBounds.width, enemyBounds.top);
	}

	//Snowball and enemy collision
	for (int e = 0; e < Enum; e++)
	{
		sf::FloatRect enemyBounds = enemies[e]->getBounds();

		for (int s = 0; s < SBnum; s++)
		{
			sf::FloatRect snowballBounds = snowball[s].getBounds();

			if (enemyBounds.intersects(snowballBounds))
			{
				enemies[e]->take_damage(1);

				// ADDED: snowball power makes encase in 1 hit
				// Check if any player has snowball power active
				bool hasSnowballPower = false;
				for (int p = 0; p < playerCount; p++)
				{
					if (players[p].isSnowballPowerActive())
					{
						hasSnowballPower = true;
						break;
					}
				}

				if (hasSnowballPower)
					enemies[e]->apply_snow_hit(999);
				else
					enemies[e]->apply_snow_hit(1);

				snowball[s].setInactive();
			}
		}
	}

	// Update projectiles
	for (int i = 0; i < projectile_count; i++)
		projectile[i]->update(0.016f);

	// Remove inactive projectiles
	int writePos = 0;
	for (int i = 0; i < projectile_count; i++)
	{
		if (projectile[i]->get_is_moving())
		{
			projectile[writePos] = projectile[i];
			writePos++;
		}
	}
	projectile_count = writePos;
}

void playState::update()
{
	for (int p = 0; p < playerCount; p++)
		players[p].update();

	// ADDED: star collection + apply chosen type until level end
	for (int p = 0; p < playerCount; p++)
	{
		starEvent.check_collection(players[p].getBounds());
	}
	std::string chosen = starEvent.consume_chosen_type();
	if (!chosen.empty())
	{
		// ADDED: award star power to all players
		for (int p = 0; p < playerCount; p++)
		{
			if (activePowerUp[p])
			{
				activePowerUp[p]->expire(players[p]);
				delete activePowerUp[p];
				activePowerUp[p] = nullptr;
			}
			activePowerUp[p] = new PowerUp_funcs(chosen, 0, 0, true); // timer = -1
			activePowerUp[p]->apply(players[p]);
		}
	}

	for (int i = 0; i < SBnum; i++)
		snowball[i].update();

	//removing dead snowballs from array to clean up space
	int writePos = 0;
	for (int i = 0; i < SBnum; i++)
	{
		if (snowball[i].getActivity())
		{
			snowball[writePos] = snowball[i];
			writePos++;
		}
	}
	SBnum = writePos;


	//=====================================
	for (int i = 0; i < Enum; i++)
	{
		// FIXED: use dynamic_cast so non-Tornado enemies are skipped safely
		Tornado* tornado = dynamic_cast<Tornado*>(enemies[i]);
		if (!tornado)
			continue;

		// Send position of closest player to the tornado
		float closestDist = 999999;
		int closestPlayer = 0;

		for (int p = 0; p < playerCount; p++)
		{
			float dist = abs(players[p].getBounds().left - tornado->get_pos_x());
			if (dist < closestDist)
			{
				closestDist = dist;
				closestPlayer = p;
			}
		}

		tornado->set_player_position(players[closestPlayer].getBounds().left,
			players[closestPlayer].getBounds().top);
	}

	for (int i = 0; i < Enum; i++)
		enemies[i]->update(0.016f);

	//===================== ADDED: power-up pickup + timer =====================
// Collect drops (stays on screen until collected)
	int dropWrite = 0;
	for (int i = 0; i < dropCount; i++)
	{
		sf::FloatRect dropBounds(drops[i]->get_pos_x(), drops[i]->get_pos_y(), 30.f, 30.f);
		bool collected = false;

		// ADDED: check collision with all players
		for (int p = 0; p < playerCount; p++)
		{
			sf::FloatRect pb = players[p].getBounds();
			if (pb.intersects(dropBounds))
			{
				if (activePowerUp[p])
				{
					activePowerUp[p]->expire(players[p]);
					delete activePowerUp[p];
					activePowerUp[p] = nullptr;
				}

				activePowerUp[p] = drops[i];
				activePowerUp[p]->apply(players[p]);
				collected = true;
				break; // One player picks it up
			}
		}

		if (!collected)
		{
			drops[dropWrite++] = drops[i];
		}
	}
	dropCount = dropWrite;

	// Update active power-up timer and expire timed ones
	for (int p = 0; p < playerCount; p++)
	{
		if (activePowerUp[p])
		{
			activePowerUp[p]->update(0.016f);
			float t = activePowerUp[p]->get_timer();
			if (t != -1.0f && t <= 0.0f)
			{
				activePowerUp[p]->expire(players[p]);
				delete activePowerUp[p];
				activePowerUp[p] = nullptr;
			}
		}
	}

	// Remove dead enemies
	int enemyWritePos = 0;
	for (int i = 0; i < Enum; i++)
	{
		if (enemies[i]->get_hp() > 0)
		{
			enemies[enemyWritePos] = enemies[i];
			enemyWritePos++;
		}
		else
		{
			int pointsEarned = 0;
			std::string enemyType = enemies[i]->get_type();

			if (enemyType == "Botom")
				pointsEarned = 100 + rand() % 401;
			else if (enemyType == "FlyingFooga")
				pointsEarned = 200 + rand() % 601;
			else if (enemyType == "Tornado")
				pointsEarned = 300 + rand() % 901;
			else if (enemyType == "Mogera")
			{
				pointsEarned = 5000;
				spawnGemRain(200, false);
			}
			else if (enemyType == "Gamakichi")
			{
				pointsEarned = 10000;
				spawnGemRain(500, false);
			}
			else if (enemyType == "Mogera_child")
				pointsEarned = 50 + rand() % 51;


			// ADDED: award points to all players
			for (int p = 0; p < playerCount; p++)
			{
				players[p].addScore(pointsEarned);
			}

			// ADDED: spawn power-up drop when enemy dies (stays until collected)
			if (dropCount < MAX_DROPS)
			{
				int roll = rand() % 100;
				if (roll < 35)
				{
					std::string pool[] = { "speed", "snowball", "distance", "balloon" };
					std::string type = pool[rand() % 4];
					float x = enemies[i]->getBounds().left;
					float y = enemies[i]->getBounds().top;
					drops[dropCount++] = new PowerUp_funcs(type, x, y, false);
				}
			}

			delete enemies[i];
		}
	}
	Enum = enemyWritePos;

	// Level 4 & 9: cash rain when all enemies dead====================
	if ((level == 4 || level == 9) && Enum == 0 && gemCount == 0 && !levelTransitioning)
	{
		spawnGemRain(50, true);
	}

	updateGems(0.016f);
	checkGemCollisions();

	// Check if all enemies are dead and no gem rain is active
	if (Enum == 0 && gemCount == 0 && !levelTransitioning)
	{
		levelTransitioning = true;
		levelTransitionTimer = 10.0f;
		nextLevel = level + 1;
	}

	// Handle level transition
	if (levelTransitioning)
	{
		levelTransitionTimer -= 0.016f;
		if (levelTransitionTimer <= 0)
		{
			// Load next level
			if (nextLevel <= 10)
			{
				level = nextLevel;
				loadLevel(level);
				levelTransitioning = false;
				levelTransitionTimer = 0.0f;
			}
			else
			{
				machine->changeState(new menuState(machine));
			}
		}
	}

	// Update HUD with current game state=======================================
	hud.update_values(players[0].getScore(), players[0].getLives(), players[0].getGems(), level, "", 0, false, 0, 1);
}

void playState::render(sf::RenderWindow& window)
{
	for (int i = 0; i < Pnum; i++)
		platform[i].render(window);

	for (int i = 0; i < Enum; i++)
		enemies[i]->draw(window);

	for (int p = 0; p < playerCount;p++)
		players[p].render(window);

	window.draw(text);

	for (int i = 0; i < SBnum; i++)
		snowball[i].render(window);

	for (int i = 0; i < projectile_count; i++)
		projectile[i]->draw(window);

	// ADDED: draw power-up drops
	for (int i = 0; i < dropCount; i++)
		drops[i]->draw(window);

	// ADDED: draw star + overlay
	starEvent.draw_star(window);
	starEvent.draw_types(window);

	// ADDED: handle clicking star choices
	if (starEvent.get_showing_types())
	{
		bool mouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		if (mouseDown && !wasMousePressed)
		{
			sf::Vector2i pixel = sf::Mouse::getPosition(window);
			sf::Vector2f world = window.mapPixelToCoords(pixel);
			starEvent.handle_click(world, players[0]);
			wasMousePressed = true;
		}
		else if (!mouseDown)
		{
			wasMousePressed = false;
		}
	}

	renderGems(window);
	hud.draw(window);
}

playState:: ~playState()
{
	// ADDED: clean up heap allocations
	for (int i = 0; i < Enum; i++)
		delete enemies[i];

	for (int i = 0; i < dropCount; i++)
		delete drops[i];
	for (int p = 0; p < 2; p++)
	{
		if (activePowerUp[p])
			delete activePowerUp[p];
	}
}

int playState::getScore()
{
	return score;
}

// --- rest of file unchanged (gem rain, HUD, getLevel/setLevel) ---
void playState::spawnGemRain(int amount, bool isCash)
{
	gemCount = 0;
	isCashRain = isCash;

	if (isCash)
		cashTimer = 10.0f;

	for (int i = 0; i < amount && gemCount < MAX_GEMS; i++)
	{
		gemX[gemCount] = rand() % 700;
		gemY[gemCount] = 0;
		gemVelocity[gemCount] = 0;
		gemCollected[gemCount] = false;
		gemCount++;
	}
}

void playState::updateGems(float deltaTime)
{
	if (isCashRain)
		cashTimer -= deltaTime;

	for (int i = 0; i < gemCount; i++)
	{
		if (!gemCollected[i])
		{
			gemVelocity[i] += 0.2f;
			gemY[i] += gemVelocity[i];

			if (gemY[i] > 650)
				gemY[i] = 650;
		}
	}

	if (isCashRain && cashTimer <= 0)
		gemCount = 0;
}

void playState::checkGemCollisions()
{
	for (int i = 0; i < gemCount; i++)
	{
		if (!gemCollected[i])
		{
			sf::FloatRect gemBounds(gemX[i], gemY[i], 15.0f, 15.0f);

			// Check collision with all players
			for (int p = 0; p < playerCount; p++)
			{
				sf::FloatRect playerBounds = players[p].getBounds();

				if (playerBounds.intersects(gemBounds))
				{
					gemCollected[i] = true;
					if (isCashRain)
					{
						players[p].addScore(500);
						players[p].addGems(10);
					}
					else
					{
						players[p].addGems(1);
					}
					break;  // Only one player can collect each gem
				}
			}
		}
	}

	int writePos = 0;
	for (int i = 0; i < gemCount; i++)
	{
		if (!gemCollected[i])
		{
			gemX[writePos] = gemX[i];
			gemY[writePos] = gemY[i];
			gemVelocity[writePos] = gemVelocity[i];
			gemCollected[writePos] = gemCollected[i];
			writePos++;
		}
	}
	gemCount = writePos;
}

void playState::renderGems(sf::RenderWindow& window)
{
	for (int i = 0; i < gemCount; i++)
	{
		if (!gemCollected[i])
		{
			if (isCashRain)
			{
				// Cash: Green square
				sf::RectangleShape cash(sf::Vector2f(12.0f, 12.0f));
				cash.setPosition(gemX[i], gemY[i]);
				cash.setFillColor(sf::Color::Green);
				window.draw(cash);
			}
			else
			{
				// Gems: Yellow circle
				sf::CircleShape gem(7.0f);
				gem.setPosition(gemX[i], gemY[i]);
				gem.setFillColor(sf::Color::Yellow);
				window.draw(gem);
			}
		}
	}
}

int playState::getLevel()
{
	return level;
}

void playState::setLevel(int lv)
{
	level = lv;
}

bool playState::setMultiplayer(bool multiplayer)
{
	return multiplayer;
}
