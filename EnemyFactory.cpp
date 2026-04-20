#include "EnemyFactory.h"
#include "Botom.h"
#include "FlyingFooga.h"
#include "Tornado.h"
#include "Mogera.h"
#include "Gamakichi.h"
#include "Mogera_child.h"

float speed_mult(int level) {
    if (level <= 5) {
        return 1.0f;
    }
    else if (level <= 7) {
        return 1.25f;
    }                               //decides speed of enemies based on level
    else if (level <= 8) {
        return 1.5f;
    }
    else {
        return 1.75f;
    }
}

int extra_hits(int level) {
    if (level <= 5) {
        return 0;
    }
    else if (level <= 7) {
        return 1;
    }                        //the number of extra hits a player gets based on levl
    else if (level <= 8) {
        return 2;
    }
    else {
        return 3;
    }
}

Enemy* EnemyFactory::create(std::string type, int level) {

    float speed = speed_mult(level);
    int hits = extra_hits(level);

    if (type == "Botom") {
        return new Botom(speed, hits);
    }
    else if (type == "FlyingFooga") {
        return new FlyingFooga(speed, hits);
    }
    else if (type == "Tornado") {
        return new Tornado(speed, hits);
    }
    else if (type == "Mogera") {
        return new Mogera();
    }
    else if (type == "Gamakichi") {
        return new Gamakichi();
    }
    if (type == "Mogera_child") {
        return new Mogera_child();
    }
    else {
        return nullptr;
    }
}