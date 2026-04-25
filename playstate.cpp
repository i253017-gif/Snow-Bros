#include<SFML/Graphics.hpp>
#include<iostream>
#include"menustate.h"
#include"playstate.h"
#include"snowball.h"
#include"player.h"
//other states

playState::playState(stateMachine* m)
{
	machine = m;
	SBnum = 0; 
	wasSpacePressed = false;
	Pnum = 0;

	loadLevel(1);
}

void playState::loadLevel(int levelNum)
{
	if (levelNum == 1)
	{
		platform[Pnum++] = Platform(150, 100, 350, 30);
		platform[Pnum++] = Platform(50, 300, 200, 30);
		platform[Pnum++] = Platform(400, 300, 200, 30);
		platform[Pnum++] = Platform(140, 480, 370, 30);
	}
	else if (levelNum == 2)
	{
		platform[Pnum++] = Platform(100, 500, 300, 30);
		platform[Pnum++] = Platform(250, 450, 150, 20);
		platform[Pnum++] = Platform(450, 350, 150, 20);
		platform[Pnum++] = Platform(200, 250, 150, 20);
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

	// ===== SCREEN BOUNDARIES (KEEP PLAYER IN) =====
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
}
	
void playState::render(sf::RenderWindow& window)
{
	for(int i=0; i<Pnum; i++)
		platform[i].render(window);


	player.render(window);

	window.draw(text);

	for (int i = 0; i < SBnum; i++)
		snowball[i].render(window);
}
playState:: ~playState()
{
	// Empty is fine
}
