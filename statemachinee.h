#pragma once
#include <SFML/Graphics.hpp>
#include "gamestate.h"
#include "inputmanager.h"

// ============================================================
// statemachinee.h
// Written by: Abiha (Student A) - updated for login integration
// ============================================================

class stateMachine {
private:
    gameState* currentState;

public:
    stateMachine() : currentState(nullptr) {}

    ~stateMachine() {
        delete currentState;
    }

    void changeState(gameState* newState) {
        delete currentState;
        currentState = newState;
    }

    void handleInput(inputManager& input) {
        if (currentState)
            currentState->handleInput(input);
    }

    void update() {
        if (currentState)
            currentState->update();
    }

    void render(sf::RenderWindow& window) {
        if (currentState)
            currentState->render(window);
    }

    // passes text input to current state
    void handleTextInput(sf::Uint32 character) {
        if (currentState)
            currentState->handle_text_input(character);
    }

    // passes mouse click to current state
    void handleMouseClick(sf::Vector2f mouse_pos) {
        if (currentState)
            currentState->handle_mouse_click(mouse_pos);
    }

    gameState* getCurrentState() { return currentState; }
};