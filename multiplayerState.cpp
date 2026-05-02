#include "multiplayerState.h"
#include "playState.h"

modeSelectionState::modeSelectionState(stateMachine* m)
{
    machine = m;
}

void modeSelectionState::handleInput(inputManager& input)
{

    if (input.isNum1Pressed())
    {
        playState* newGame = new playState(machine);
        newGame->setMultiplayer(false);  // Singleplayer
        machine->changeState(newGame);
    }

    if (input.isNum2Pressed())
    {
        playState* newGame = new playState(machine);
        newGame->setMultiplayer(true);   // Multiplayer
        machine->changeState(newGame);
    }
}

void modeSelectionState::update()
{
    // Nothing to update
}

void modeSelectionState::render(sf::RenderWindow& window)
{
    //ishmal add your ui here
    window.clear(sf::Color::Black);

}

modeSelectionState::~modeSelectionState()
{
}
