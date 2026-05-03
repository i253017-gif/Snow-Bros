#pragma once
#include <SFML/Graphics.hpp>
#include "inputmanager.h"

// ============================================================
// gamestate.h
// Abstract base class for all game states
// Written by: Abiha (Student A) - updated for login integration
// ============================================================

class gameState {
public:
    virtual void handleInput(inputManager& input) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    // empty defaults - only login/register states override these
    virtual void handle_text_input(sf::Uint32 character) {};
	virtual void handle_mouse_click(sf::Vector2f mouse_pos) {};

    virtual ~gameState();
};

//base class for states