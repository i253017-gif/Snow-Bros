#pragma once
#include "Enemy.h"
#include <string>

//returns correct enemy

class EnemyFactory {
public:
    static Enemy* create(std::string type, int level); /*pointer is being returned bc enemy is abstract
    and also to prevent object slicing*/

    //static so that objevt isnt created again and again


};
