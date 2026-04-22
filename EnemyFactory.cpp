#include "EnemyFactory.h"
#include "Bottom.h"
#include "FlyingFooga.h"
#include "Tornado.h"
#include "Mogera.h"
#include "Gamakichi.h"
#include "Mogera_child.h"
#include"ColorVariant.h"


Enemy* EnemyFactory::create(std::string type, int level) {
    bool use_variant;
    if (level >= 6 && type != "Mogera" && type != "Gamakichi"
        && type != "Mogera_child")
    {
        use_variant = true;
    }
    else
        use_variant = false;
    

    if (type == "Botom") {
        Botom* b = new Botom(0,0,1,1);
        if (use_variant) {
            return new ColorVariant(b, level, "Botom");
        }
        return b;
    }
    else if (type == "FlyingFooga") {
        FlyingFooga* f = new FlyingFooga(0,0,1,0);
        if (use_variant) {
            return new ColorVariant(f, level, "FlyingFooga");
        }
        return f;
    }
    else  if (type == "Tornado") {
        Tornado* t = new Tornado(0,0,1,0);
        if (use_variant)
        {
            return new ColorVariant(t, level, "Tornado");
        }
        return t;
    }
    else   if (type == "Mogera") {
        return new Mogera(400,300,200);
    }
    else if (type == "Gamakichi") {
        return new Gamakichi(400,400,500);
    }
    else if (type == "Mogera_child") {
        return new Mogera_child(0, 0, 1, 0);
    }

    // if unknown type to prevent memory leak
    return nullptr;
}
