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
//other states

playState::playState(stateMachine* m)
{
	machine = m;
	SBnum = 0; 
	wasSpacePressed = false;
	Pnum = 0;
	Enum = 0;

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


		enemies[Enum++] = new Tornado(300, 150, 1.0f, 0);
		enemies[Enum++] = new Tornado(400, 200, 1.2f, 0);
		enemies[Enum++] = new Tornado(200, 250, 0.8f, 1);
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
		}
		Enum = enemyWritePos;

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
}
playState:: ~playState()
{
	// Empty is fine
}
