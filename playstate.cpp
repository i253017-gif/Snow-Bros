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

	//nikal dena=====================================================================
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setString("PLAY STATE\nW = Jump | A/D = Move\nESC = Menu");
	text.setCharacterSize(20);
	text.setPosition(50, 20);
	//============================================================================

	SBnum = 0; 
	wasSpacePressed = false;
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
	player.render(window);

	window.draw(text);

	for (int i = 0; i < SBnum; i++)
		snowball[i].render(window);
}
playState:: ~playState()
{
	// Empty is fine
}
