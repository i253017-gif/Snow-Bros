#include"gamestate.h"
#include "stateMachinee.h"
#include "inputManager.h"

class modeSelectionState: public gameState
{
private:
    stateMachine* machine;

public:
    modeSelectionState(stateMachine* m);
    void handleInput(inputManager& input);
    void update();
    void render(sf::RenderWindow& window);
    ~modeSelectionState();
};
