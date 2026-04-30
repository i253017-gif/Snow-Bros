#include"pause.h"

pause::pause(stateMachine* m) : machine(m) {
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	// background
	bg_texture.loadFromFile("images/pause_bg.png");
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale(
		700.f / bg_texture.getSize().x,
		700.f / bg_texture.getSize().y
	);
	// --- 2 buttons on left side ---
	float button_x = 150;   // x position of buttons
	float button_y = 300;   // starting y position
	float button_width = 150;   // button width
	float button_height = 50;    // button height
	float button_gap = 70;    // gap between buttons
	for (int i = 0; i < 2; i++) {
		// button box - dark orange
		button[i].setSize(sf::Vector2f(button_width, button_height));
		button[i].setPosition(button_x, button_y + (i * button_gap));
		button[i].setFillColor(sf::Color(180, 80, 0));         // dark orange
		// button text - white
		button_text[i].setFont(font);
		button_text[i].setString(button_name[i]);
		button_text[i].setCharacterSize(20);
		button_text[i].setFillColor(sf::Color::White);
		button_text[i].setStyle(sf::Text::Bold);
		// center text inside button
		float text_x = button_x + (button_width / 2) - (button_text[i].getGlobalBounds().width / 2);
		float text_y = button_y + (i * button_gap) + (button_height / 2) - 12;
		button_text[i].setPosition(text_x, text_y);
	}
	// --- 2 buttons on right side ---
	button_x = 400;   // x position of buttons
	button_y = 300;   // starting y position
	for (int i = 0; i < 2; i++) {
		// button box - dark orange
		button_2[i].setSize(sf::Vector2f(button_width, button_height));
		button_2[i].setPosition(button_x, button_y + (i * button_gap));
		button_2[i].setFillColor(sf::Color(180, 80, 0));         // dark orange
		// button text - white
		button_text2[i].setFont(font);
		button_text2[i].setString(button_name2[i]);
		button_text2[i].setCharacterSize(20);
		button_text2[i].setFillColor(sf::Color::White);
		button_text2[i].setStyle(sf::Text::Bold);
		// center text inside button
		float text_x = button_x + (button_width / 2) - (button_text2[i].getGlobalBounds().width / 2);
		float text_y = button_y + (i * button_gap) + (button_height / 2) - 12;
		button_text2[i].setPosition(text_x, text_y);
	}
	// --- 1 button on bottom centre ---
	button3.setSize(sf::Vector2f(250, 50));
	button3.setPosition(225, 500)
		;
	button3.setFillColor(sf::Color(180, 80, 0));         // dark orange
	button_text3.setFont(font)
		;
	button_text3.setString(button_name3);
	button_text3.setCharacterSize(20);
	button_text3.setFillColor(sf::Color::White);
	button_text3.setStyle(sf::Text::Bold);
		// center text inside button
		float text_x = 350 - (button_text3.getGlobalBounds().width / 2);
		float text_y = 500 + (25) - 12;
		button_text3.setPosition(text_x, text_y);

}

void pause::render(sf::RenderWindow& window) {
	window.draw(bg_sprite);
	for (int i = 0; i < 2; i++) {
		window.draw(button[i]);
		window.draw(button_text[i]);
	}
	for (int i = 0; i < 2; i++) {
		window.draw(button_2[i]);
		window.draw(button_text2[i]);
	}
	window.draw(button3);
	window.draw(button_text3);
}
void pause::handle_mouse_click(sf::Vector2f mp) {
	// Resume
	if (button[0].getGlobalBounds().contains(mp)) {
		//machine->changeState(new menu(machine));
	}
	// Save
	if (button[1].getGlobalBounds().contains(mp)) {
		// machine->changeState(new SaveState(machine));
	}
	// Shop
	if (button_2[0].getGlobalBounds().contains(mp)) {
		// machine->changeState(new ShopState(machine));
	}
	// Logout
	if (button_2[1].getGlobalBounds().contains(mp)) {
		// machine->changeState(new LoginState(machine));
	}
	// Exit to Main Menu
	if (button3.getGlobalBounds().contains(mp)) {
		exit(0);
	}
}