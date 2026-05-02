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
	powerup_count = 0;

	lives = 2;
	score = 0;
	srand(time(0));
	loadLevel(1);
}

void playState::loadLevel(int levelNum)
{
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
		platform[Pnum++] = Platform(100, 500, 300, 30);
		platform[Pnum++] = Platform(250, 450, 150, 20);
		platform[Pnum++] = Platform(450, 350, 150, 20);
		platform[Pnum++] = Platform(200, 250, 150, 20);

		enemies[Enum++] = new Botom(250, 200, 1.0f, 0);
		enemies[Enum++] = new Botom(350, 150, 1.3f, 1);
		enemies[Enum++] = new Botom(150, 250, 0.9f, 0);
		enemies[Enum++] = new Botom(450, 100, 1.1f, 1);
	}
}

void playState::handleInput(inputManager& input)
{
	if (input.isEscapePressed())
		machine->changeState(new menuState(machine));
	//pressing esp while playing will take us to menu


	if (input.isSpacePressed() && SBnum<100 && !wasSpacePressed)
	{											//!wasSpacePressed makes sure last press wasnt a space
		float startX = player.getBounds().left;
		if (player.getFacingDirection() == 1)
			startX += player.getBounds().width;
		float startY = player.getBounds().top + player.getBounds().height / 2;
		snowball[SBnum] = Snowball(startX, startY, player.getFacingDirection(), 5.0f, 500.0f);
		SBnum++;
		wasSpacePressed = true;
	}
	else if (!input.isSpacePressed())
	{
		wasSpacePressed = false;  // Space released, ready for next press
	}


	player.handleInput(input);


	player.setOnGround(false);  // Reset

	for (int i = 0; i < Pnum; i++)
	{
		sf::FloatRect playerBounds = player.getBounds();
		sf::FloatRect platformBounds = platform[i].getBounds();

		if (playerBounds.intersects(platformBounds))
		{
			if (player.getVelocity() > 0)
			{
				player.newPosition(playerBounds.left,
					platformBounds.top - playerBounds.height);
				player.setVelocity(0);
				player.setOnGround(true);
			}
		}
	}

	//======================================================================
	//SCREEN BOUNDARIES FOR PLAYER
	sf::FloatRect playerBounds = player.getBounds();

	// Left boundary
	if (playerBounds.left < 0)
		player.newPosition(0, playerBounds.top);

	// Right boundary
	if (playerBounds.left + playerBounds.width > 700)
		player.newPosition(700 - playerBounds.width, playerBounds.top);

	// Bottom boundary - just push player back up
	if (playerBounds.top > 700)
		player.newPosition(playerBounds.left, 700 - playerBounds.height);



	//PLAYER AND ENEMY COLLISIONS
	
	if (!player.isInvincible())
	{
		sf::FloatRect playerBounds = player.getBounds();
		for (int i = 0; i < Enum; i++)
		{
			sf::FloatRect enemyBounds = enemies[i]->getBounds();
			if (playerBounds.intersects(enemyBounds))
			{
				player.loseLive();
				break; // Only lose one life per frame, even if colliding with multiple enemies
			}
		}
		if (player.getLives() <= 0)
		{
			//ADD GAME OVER SCREEN AND SHIT
			//FOR NOW END GAME
			machine->changeState(new menuState(machine));
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

	//Snoeball and enemy collision
	for (int e = 0; e < Enum; e++)
	{
		sf::FloatRect enemyBounds = enemies[e]->getBounds();

		for (int s = 0; s < SBnum; s++)
		{
			sf::FloatRect snowballBounds = snowball[s].getBounds();

			if (enemyBounds.intersects(snowballBounds))
			{
				enemies[e]->take_damage(1);
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
	player.update();


	for (int i = 0; i < SBnum; i++)
		snowball[i].update();

	//================SAMAJHNA HAY THORA===================
	//removing dead nowballs from array to clean up space
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

	// SEND PLAYER POSITION TO ALL ENEMIES=============================
	for (int i = 0; i < Enum; i++)
	{
		Tornado* tornado = (Tornado*)enemies[i];
		tornado->set_player_position(player.getBounds().left, player.getBounds().top);
	}

		for (int i = 0; i < Enum; i++)
			enemies[i]->update(0.016f);

	//MOGERA LOGIC AND MOGERA CHILDREN
	// ===== MOGERA-SPECIFIC LOGIC =====
		for (int i = 0; i < Enum; i++)
		{
			Mogera* mogera = dynamic_cast<Mogera*>(enemies[i]);
			if (mogera != nullptr)
			{
				// Spawn MogeraChild
				if (mogera->get_child_count_down() >= mogera->get_child_spawn_timer())
				{
					int spawnCount = rand() % 3 + 1;  

					for (int c = 0; c < spawnCount; c++)
					{
						if (Enum < 500) 
						{
							// Spawn from Mogeras mouth area 
							float spawnX = mogera->get_pos_x() + 75;  
							float spawnY = mogera->get_pos_y() + 20; 

							enemies[Enum++] = new Mogera_child(spawnX, spawnY, -1.0f, 0.0f);
						}
					}
					mogera->set_child_timer(0.0f);  // Reset timer
				}

				// Platform collision for Mogera (transparent logic)
				sf::FloatRect mogeraBounds = mogera->getBounds();
				if (!mogera->get_is_transparent())  // Only collide if NOT transparent
				{
					for (int p = 0; p < Pnum; p++)
					{
						sf::FloatRect platformBounds = platform[p].getBounds();

						if (mogeraBounds.intersects(platformBounds))
						{
							// Check if Mogera is falling onto platform
							if (mogera->get_velocity() > 0)
							{
								mogera->newPosition(mogeraBounds.left,
									platformBounds.top - mogeraBounds.height);
								mogera->set_velocity(0);
								mogera->setOnPlatform(true);
							}
						}
					}
				}
			}
		}


		//GAMACHIKI LOGIC
		// GAMAKICHI ROCKET SPAWNING
		for (int i = 0; i < Enum; i++)
		{
			Gamakichi* gamachiki = dynamic_cast<Gamakichi*>(enemies[i]);
			if (gamachiki != nullptr && gamachiki->get_rocket_timer() >= gamachiki->get_rocket_spawn_interval())
			{
				int rocket_count = 0;
				RocketData* rockets = gamachiki->get_rockets_to_spawn(rocket_count);

				for (int r = 0; r < rocket_count; r++)
				{
					if (projectile_count < 500)
					{
						projectile[projectile_count++] = new artillery_rocket(
							rockets[r].x, rockets[r].y,
							rockets[r].vx, rockets[r].vy,
							rockets[r].blast_radius
						);
					}
				}

				gamachiki->set_rocket_timer(0.0f);
			}
		}
		// POWERUPS
		updatePowerUps(0.016f);

		// CHECK FOR POWER-UP COLLECTION - ADD THIS HERE
		checkPowerUpCollisions();

		// Check for power-up expiration and remove expired ones
		for (int i = 0; i < powerup_count; i++)
		{
			if (powerups[i]->get_timer() <= 0 && powerups[i]->get_powerup_type() != "snowball" && powerups[i]->get_powerup_type() != "distance")
			{
				// Effect has expired, remove it
				powerups[i]->expire(player);
				removePowerUp(i);
				i--;
			}
		}
		//check bounds again to make sure it doesnt move out of frame after update
		for (int e = 0; e < Enum; e++)
		{
			sf::FloatRect enemyBounds = enemies[e]->getBounds();

			if (enemyBounds.left < 0)
				enemies[e]->newPosition(0, enemyBounds.top);
			if (enemyBounds.left + enemyBounds.width > 700)
				enemies[e]->newPosition(700 - enemyBounds.width, enemyBounds.top);
			if (enemyBounds.top < 0)
				enemies[e]->newPosition(enemyBounds.left, 0);
			if (enemyBounds.top + enemyBounds.height > 700)
				enemies[e]->newPosition(enemyBounds.left, 700 - enemyBounds.height);
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

				player.addScore(pointsEarned);
				spawnPowerUp(enemies[i]->get_pos_x(), enemies[i]->get_pos_y());
				delete enemies[i];
			}
		}
		Enum = enemyWritePos;

		// Level 4 & 9: cash rain when all enemies dead
		if ((level == 4 || level == 9) && Enum == 0 && gemCount == 0)
		{
			spawnGemRain(50, true);
		}

		updateGems(0.016f);
		checkGemCollisions();

		// Update HUD with current game state=========================================================
		hud.update_values(player.getScore(), player.getLives(), player.getGems(), level, "", 0, false, 0, 1);
	}

	
void playState::render(sf::RenderWindow& window)
{
	for(int i=0; i<Pnum; i++)
		platform[i].render(window);

	for (int i = 0; i < Enum; i++)
		enemies[i]->draw(window);

	player.render(window);

	window.draw(text);

	for (int i = 0; i < SBnum; i++)
		snowball[i].render(window);

	for (int i = 0; i < projectile_count; i++)
		projectile[i]->draw(window);

	for (int i = 0; i < powerup_count; i++)
		powerups[i]->draw(window);

	hud.draw(window);
}
playState:: ~playState()
{
	// Empty is fine
}

void playState::spawnPowerUp(float x, float y)
{
	// Array of possible power-up types
	std::string powerup_types[] = { "speed", "snowball", "distance", "balloon" };

	// Randomly select a power-up type
	int random_type = rand() % 4;
	std::string selected_type = powerup_types[random_type];

	// Spawn the power-up if we have space
	if (powerup_count < 50)
	{
		powerups[powerup_count++] = new PowerUp_funcs(selected_type, x, y);
	}
}

void playState::updatePowerUps(float delta_time)
{
	for (int i = 0; i < powerup_count; i++)
	{
		powerups[i]->update(delta_time);
	}
}

void playState::checkPowerUpCollisions()
{
	sf::FloatRect playerBounds = player.getBounds();

	for (int i = 0; i < powerup_count; i++)
	{
		sf::FloatRect powerupBounds(
			powerups[i]->get_pos_x(),
			powerups[i]->get_pos_y(),
			30.0f,  // Approximate size based on visual scale
			30.0f
		);

		if (playerBounds.intersects(powerupBounds))
		{
			// Apply the power-up effect to the player
			powerups[i]->apply(player);

			// Remove the collected power-up
			removePowerUp(i);
			i--;  // Adjust index after removal
		}
	}
}

void playState::removePowerUp(int index)
{
	if (index >= 0 && index < powerup_count)
	{
		delete powerups[index];
		powerups[index] = nullptr;

		// Shift remaining power-ups
		for (int i = index; i < powerup_count - 1; i++)
		{
			powerups[i] = powerups[i + 1];
		}
		powerup_count--;
	}
}


int playState::getScore()
{
	return score;
}


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
	sf::FloatRect playerBounds = player.getBounds();

	for (int i = 0; i < gemCount; i++)
	{
		if (!gemCollected[i])
		{
			sf::FloatRect gemBounds(gemX[i], gemY[i], 15.0f, 15.0f);

			if (playerBounds.intersects(gemBounds))
			{
				gemCollected[i] = true;
				if (isCashRain)
				{
					player.addScore(500);
					player.addGems(10);
				}
				else
				{
					player.addGems(1);
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
