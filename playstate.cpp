#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "menu.h"          // CHANGED: use menu instead of menustate
#include "playstate.h"
#include "snowball.h"
#include "player.h"
#include "FlyingFooga.h"
#include "Tornado.h"
#include "Mogera.h"
#include "Mogera_child.h"
#include "Gamachiki.h"
#include "artillery_rocket.h"
#include "Projectile.h"
#include "PowerUp.h"
#include "PowerUp_funcs.h"

// CHANGED: takes username
playState::playState(stateMachine* m, std::string user)
{
    machine = m;
    username = user;
    db.set_active_user(username); // CHANGED: set active user

    SBnum = 0;
    wasSpacePressed = false;
    Pnum = 0;
    Enum = 0;
    projectile_count = 0;
    wasMousePressed = false;
    lives = 15;
    score = 0;
    srand(time(0));
    dropCount = 0;
    for (int p = 0; p < 2; p++)
        activePowerUp[p] = nullptr;
    level = 1;
    starLevel = 1 + (rand() % 10);
    playerCount = 1;
    multiplayer = false;

    loadLevel(level);
}

void playState::loadLevel(int levelNum)
{
    // CHANGED: auto save when moving to next level
    if (levelNum > 1 && !username.empty())
        db.save_data(levelNum - 1, players[0].getLives(),
            players[0].getGems(), players[0].getScore());

    for (int i = 0; i < dropCount; i++)
        delete drops[i];
    dropCount = 0;

    for (int p = 0; p < playerCount; p++)
    {
        if (activePowerUp[p])
        {
            activePowerUp[p]->expire(players[p]);
            delete activePowerUp[p];
            activePowerUp[p] = nullptr;
        }
    }

    Enum = 0;
    Pnum = 0;
    SBnum = 0;
    projectile_count = 0;
    levelTransitioning = false;
    levelTransitionTimer = 0.0f;
    players[0].newPosition(100, 100);

    if (levelNum == starLevel)
        starEvent.spawn_star(350, 250);

    if (levelNum == 1)
    {
        platform[Pnum++] = Platform(0, 100, 350, 30);
        platform[Pnum++] = Platform(0, 300, 200, 30);
        platform[Pnum++] = Platform(400, 300, 400, 30);
        platform[Pnum++] = Platform(140, 480, 370, 30);
        enemies[Enum++] = new Botom(200, 250, 0.8f, 1);
        texture.loadFromFile("images/bg.png");
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);
        sprite.setScale(700.0f / texture.getSize().x, 700.0f / texture.getSize().y);
    }
    else if (levelNum == 2)
    {
        platform[Pnum++] = Platform(0, 450, 150, 30);
        platform[Pnum++] = Platform(275, 450, 150, 30);
        platform[Pnum++] = Platform(550, 450, 150, 30);
        platform[Pnum++] = Platform(150, 300, 150, 30);
        platform[Pnum++] = Platform(400, 300, 150, 30);
        enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
        texture.loadFromFile("images/bg.png"); 
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);
        sprite.setScale(700.0f / texture.getSize().x, 700.0f / texture.getSize().y);
    }
    else if (levelNum == 3)
    {
        platform[Pnum++] = Platform(0, 450, 120, 30);
        platform[Pnum++] = Platform(150, 450, 120, 30);
        platform[Pnum++] = Platform(290, 300, 120, 30);
        platform[Pnum++] = Platform(430, 450, 120, 30);
        platform[Pnum++] = Platform(580, 450, 120, 30);
        enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
        texture.loadFromFile("images/bg.png"); 
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);
        sprite.setScale(700.0f / texture.getSize().x, 700.0f / texture.getSize().y);
    }
    else if (levelNum == 4)
    {
        platform[Pnum++] = Platform(0, 380, 250, 30);
        platform[Pnum++] = Platform(250, 250, 200, 30);
        platform[Pnum++] = Platform(650, 180, 50, 30);
        platform[Pnum++] = Platform(600, 380, 100, 30);
        enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
        texture.loadFromFile("images/bg.png");
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);
        sprite.setScale(700.0f / texture.getSize().x, 700.0f / texture.getSize().y);
    }
    else if (levelNum == 5)
    {
        platform[Pnum++] = Platform(0, 400, 170, 30);
        platform[Pnum++] = Platform(0, 280, 100, 30);
        platform[Pnum++] = Platform(0, 100, 170, 30);
        platform[Pnum++] = Platform(400, 350, 300, 50);
        enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
        texture.loadFromFile("images/bg.png"); 
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);
        sprite.setScale(700.0f / texture.getSize().x, 700.0f / texture.getSize().y);
    }
    else if (levelNum == 6)
    {
        platform[Pnum++] = Platform(50, 480, 130, 30);
        platform[Pnum++] = Platform(200, 380, 130, 30);
        platform[Pnum++] = Platform(350, 280, 130, 30);
        platform[Pnum++] = Platform(500, 380, 130, 30);
        platform[Pnum++] = Platform(620, 480, 80, 30);
        enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
        texture.loadFromFile("images/bg.png"); 
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);
        sprite.setScale(700.0f / texture.getSize().x, 700.0f / texture.getSize().y);
    }
    else if (levelNum == 7)
    {
        platform[Pnum++] = Platform(100, 450, 150, 30);
        platform[Pnum++] = Platform(275, 350, 150, 30);
        platform[Pnum++] = Platform(450, 450, 150, 30);
        platform[Pnum++] = Platform(200, 200, 300, 30);
        enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
        texture.loadFromFile("images/bg.png"); 
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);
        sprite.setScale(700.0f / texture.getSize().x, 700.0f / texture.getSize().y);
    }
    else if (levelNum == 8)
    {
        platform[Pnum++] = Platform(50, 500, 100, 30);
        platform[Pnum++] = Platform(150, 400, 100, 30);
        platform[Pnum++] = Platform(275, 300, 150, 30);
        platform[Pnum++] = Platform(500, 400, 100, 30);
        platform[Pnum++] = Platform(600, 500, 100, 30);
        enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
        texture.loadFromFile("images/bg.png"); 
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);
        sprite.setScale(700.0f / texture.getSize().x, 700.0f / texture.getSize().y);
    }
    else if (levelNum == 9)
    {
        platform[Pnum++] = Platform(75, 450, 120, 30);
        platform[Pnum++] = Platform(290, 400, 120, 30);
        platform[Pnum++] = Platform(510, 400, 120, 30);
        platform[Pnum++] = Platform(600, 450, 100, 30);
        enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
        texture.loadFromFile("images/bg.png"); 
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);
        sprite.setScale(700.0f / texture.getSize().x, 700.0f / texture.getSize().y);
    }
    else if (levelNum == 10)
    {
        platform[Pnum++] = Platform(100, 400, 150, 30);
        platform[Pnum++] = Platform(450, 400, 150, 30);
        enemies[Enum++] = new Botom(300, 150, 1.0f, 0);
        texture.loadFromFile("images/bg.png"); 
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);
        sprite.setScale(700.0f / texture.getSize().x, 700.0f / texture.getSize().y);
    }
}

void playState::handleInput(inputManager& input)
{
    if (starEvent.get_showing_types())
        return;

    // CHANGED: escape saves and goes to menu with username
    if (input.isEscapePressed())
    {
        if (!username.empty())
            db.save_data(level, players[0].getLives(),
                players[0].getGems(), players[0].getScore());
        machine->changeState(new menu(machine, username));
    }

    for (int p = 0; p < playerCount; p++)
        players[p].handleInput(input, p);

    if (input.isSpacePressed() && SBnum < 100 && !wasSpacePressed)
    {
        for (int p = 0; p < playerCount; p++)
        {
            float startX = players[p].getBounds().left;
            if (players[p].getFacingDirection() == 1)
                startX += players[p].getBounds().width;
            float startY = players[p].getBounds().top + players[p].getBounds().height / 2;
            snowball[SBnum] = Snowball(startX, startY,
                players[p].getFacingDirection(), 5.0f, 500.0f);
            SBnum++;
        }
        wasSpacePressed = true;
    }
    else if (!input.isSpacePressed())
        wasSpacePressed = false;

    for (int p = 0; p < playerCount; p++)
    {
        players[p].setOnGround(false);

        for (int i = 0; i < Pnum; i++)
        {
            sf::FloatRect playerBounds = players[p].getBounds();
            sf::FloatRect platformBounds = platform[i].getBounds();
            if (playerBounds.intersects(platformBounds))
            {
                if (players[p].getVelocity() > 0)
                {
                    players[p].newPosition(playerBounds.left,
                        platformBounds.top - playerBounds.height);
                    players[p].setVelocity(0);
                    players[p].setOnGround(true);
                }
            }
        }

        sf::FloatRect playerBounds = players[p].getBounds();
        if (playerBounds.left < 0)
            players[p].newPosition(0, playerBounds.top);
        if (playerBounds.left + playerBounds.width > 700)
            players[p].newPosition(700 - playerBounds.width, playerBounds.top);
        if (playerBounds.top > 700)
            players[p].newPosition(playerBounds.left, 700 - playerBounds.height);

        if (!players[p].isInvincible())
        {
            sf::FloatRect playerBounds = players[p].getBounds();
            for (int i = 0; i < Enum; i++)
            {
                sf::FloatRect enemyBounds = enemies[i]->getBounds();
                if (playerBounds.intersects(enemyBounds))
                {
                    players[p].loseLive();
                    break;
                }
            }
            if (players[p].getLives() <= 0)
            {
                // CHANGED: save and add to leaderboard on game over
                if (!username.empty())
                {
                    db.add_to_leaderboard(players[p].getScore(), level);
                    db.save_data(level, players[p].getLives(),
                        players[p].getGems(), players[p].getScore());
                }
                if (multiplayer && !username.empty())
                    db.add_to_leaderboard(players[1].getScore(), level);
                machine->changeState(new menu(machine, username));
            }
        }
    }

    for (int e = 0; e < Enum; e++)
    {
        enemies[e]->setOnGround(false);
        sf::FloatRect enemyBounds = enemies[e]->getBounds();

        for (int i = 0; i < Pnum; i++)
        {
            sf::FloatRect platformBounds = platform[i].getBounds();
            if (enemyBounds.intersects(platformBounds))
            {
                if (enemies[e]->getVelocity() > 0)
                {
                    enemies[e]->newPosition(enemyBounds.left,
                        platformBounds.top - enemyBounds.height);
                    enemies[e]->setVelocity(0);
                    enemies[e]->setOnGround(true);
                }
            }
        }

        if (enemyBounds.top > 700) {
            enemies[e]->newPosition(enemyBounds.left, 700 - enemyBounds.height);
            enemies[e]->setVelocity(0);
            enemies[e]->setOnGround(true);
        }
        if (enemyBounds.left < 0)
            enemies[e]->newPosition(0, enemyBounds.top);
        if (enemyBounds.left + enemyBounds.width > 700)
            enemies[e]->newPosition(700 - enemyBounds.width, enemyBounds.top);
    }

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

    for (int e = 0; e < Enum; e++)
    {
        sf::FloatRect enemyBounds = enemies[e]->getBounds();
        for (int s = 0; s < SBnum; s++)
        {
            if (snowball[s].isFrozen())
            {
                EnemyType frozenType = (EnemyType)snowball[s].getFrozenEnemyType();
                if (frozenType != MOGERA && frozenType != GAMAKICHI &&
                    enemyBounds.intersects(snowball[s].getBounds()))
                    enemies[e]->take_damage(999);
                continue;
            }

            sf::FloatRect snowballBounds = snowball[s].getBounds();
            if (enemyBounds.intersects(snowballBounds))
            {
                EnemyType enemyType = enemies[e]->getEnemyType();
                bool hasSnowballPower = false;
                for (int p = 0; p < playerCount; p++)
                {
                    if (players[p].isSnowballPowerActive())
                    {
                        hasSnowballPower = true;
                        break;
                    }
                }
                if (hasSnowballPower)
                    enemies[e]->apply_snow_hit(999);
                else
                    enemies[e]->apply_snow_hit(1);

                if (enemies[e]->get_encased() &&
                    enemyType != MOGERA && enemyType != GAMAKICHI)
                {
                    int roll = rand() % 100;
                    if (roll < 50)
                    {
                        snowball[s].freezeEnemy(enemyType,
                            enemies[e]->getBounds().left,
                            enemies[e]->getBounds().top);
                        enemies[e]->take_damage(999);
                        continue;
                    }
                    else
                        enemies[e]->take_damage(999);
                }
                snowball[s].setInactive();
            }
        }
    }

    for (int i = 0; i < projectile_count; i++)
        projectile[i]->update(0.016f);

    writePos = 0;
    for (int i = 0; i < projectile_count; i++)
    {
        if (projectile[i]->get_is_moving())
        {
            projectile[writePos] = projectile[i];
            writePos++;
        }
    }
    projectile_count = writePos;
}

void playState::update()
{
    for (int p = 0; p < playerCount; p++)
        players[p].update();

    for (int p = 0; p < playerCount; p++)
        starEvent.check_collection(players[p].getBounds());

    std::string chosen = starEvent.consume_chosen_type();
    if (!chosen.empty())
    {
        for (int p = 0; p < playerCount; p++)
        {
            if (activePowerUp[p])
            {
                activePowerUp[p]->expire(players[p]);
                delete activePowerUp[p];
                activePowerUp[p] = nullptr;
            }
            activePowerUp[p] = new PowerUp_funcs(chosen, 0, 0, true);
            activePowerUp[p]->apply(players[p]);
        }
    }

    for (int i = 0; i < SBnum; i++)
        snowball[i].update();

    for (int i = 0; i < Enum; i++)
    {
        if (enemies[i]->get_type() == "Tornado")
        {
            Tornado* tornado = (Tornado*)enemies[i];
            float closestDist = 999999;
            int closestPlayer = 0;
            for (int p = 0; p < playerCount; p++)
            {
                float dist = abs(players[p].getBounds().left - tornado->get_pos_x());
                if (dist < closestDist)
                {
                    closestDist = dist;
                    closestPlayer = p;
                }
            }
            tornado->set_player_position(
                players[closestPlayer].getBounds().left,
                players[closestPlayer].getBounds().top);
        }
        enemies[i]->update(0.016f);
    }

    int dropWrite = 0;
    for (int i = 0; i < dropCount; i++)
    {
        sf::FloatRect dropBounds(drops[i]->get_pos_x(),
            drops[i]->get_pos_y(), 30.f, 30.f);
        bool collected = false;

        for (int p = 0; p < playerCount; p++)
        {
            sf::FloatRect pb = players[p].getBounds();
            if (pb.intersects(dropBounds))
            {
                if (activePowerUp[p])
                {
                    activePowerUp[p]->expire(players[p]);
                    delete activePowerUp[p];
                    activePowerUp[p] = nullptr;
                }
                activePowerUp[p] = drops[i];
                activePowerUp[p]->apply(players[p]);
                collected = true;
                break;
            }
        }

        if (!collected)
            drops[dropWrite++] = drops[i];
    }
    dropCount = dropWrite;

    for (int p = 0; p < playerCount; p++)
    {
        if (activePowerUp[p])
        {
            activePowerUp[p]->update(0.016f);
            float t = activePowerUp[p]->get_timer();
            if (t != -1.0f && t <= 0.0f)
            {
                activePowerUp[p]->expire(players[p]);
                delete activePowerUp[p];
                activePowerUp[p] = nullptr;
            }
        }
    }

    int enemyWritePos = 0;
    for (int i = 0; i < Enum; i++)
    {
        if (enemies[i]->get_hp() > 0)
        {
            enemies[enemyWritePos] = enemies[i];
            enemyWritePos++;
        }
        else
        {
            int pointsEarned = 0;
            EnemyType enemyType = enemies[i]->getEnemyType();

            if (enemyType == BOTOM)
                pointsEarned = 100 + rand() % 401;
            else if (enemyType == FLYING_FOOGA)
                pointsEarned = 200 + rand() % 601;
            else if (enemyType == TORNADO)
                pointsEarned = 300 + rand() % 901;
            else if (enemyType == MOGERA)
            {
                pointsEarned = 5000;
                spawnGemRain(200, false);
            }
            else if (enemyType == GAMAKICHI)
            {
                pointsEarned = 10000;
                spawnGemRain(500, false);
            }
            else if (enemyType == MOGERA_CHILD)
                pointsEarned = 50 + rand() % 51;

            for (int p = 0; p < playerCount; p++)
                players[p].addScore(pointsEarned);

            if (dropCount < MAX_DROPS)
            {
                int roll = rand() % 100;
                if (roll < 35)
                {
                    std::string pool[] = { "speed", "snowball", "distance", "balloon" };
                    std::string type = pool[rand() % 4];
                    float x = enemies[i]->getBounds().left;
                    float y = enemies[i]->getBounds().top;
                    drops[dropCount++] = new PowerUp_funcs(type, x, y, false);
                }
            }
            delete enemies[i];
        }
    }
    Enum = enemyWritePos;

    if ((level == 4 || level == 9) && Enum == 0 && gemCount == 0 && !levelTransitioning)
        spawnGemRain(10, true);

    updateGems(0.016f);
    checkGemCollisions();

    if (Enum == 0 && gemCount == 0 && !levelTransitioning)
    {
        levelTransitioning = true;
        levelTransitionTimer = 10.0f;
        nextLevel = level + 1;
    }

    if (levelTransitioning)
    {
        levelTransitionTimer -= 0.016f;
        if (levelTransitionTimer <= 0)
        {
            if (nextLevel <= 10)
            {
                level = nextLevel;
                loadLevel(level);
                levelTransitioning = false;
                levelTransitionTimer = 0.0f;
            }
            else
            {
                // CHANGED: game complete - add to leaderboard and go to menu
                if (!username.empty())
                {
                    db.add_to_leaderboard(players[0].getScore(), level);
                    if (multiplayer)
                        db.add_to_leaderboard(players[1].getScore(), level);
                    db.save_data(level, players[0].getLives(),
                        players[0].getGems(), players[0].getScore());
                }
                machine->changeState(new menu(machine, username));
            }
        }
    }

    hud.update_values(players[0].getScore(), players[0].getLives(),
        players[0].getGems(), level, "", 0, false, 0, 1);
}

void playState::render(sf::RenderWindow& window)
{
    window.draw(sprite);

    for (int i = 0; i < Pnum; i++)
        platform[i].render(window);

    for (int i = 0; i < Enum; i++)
        enemies[i]->draw(window);

    for (int p = 0; p < playerCount; p++)
        players[p].render(window);

    window.draw(text);

    for (int i = 0; i < SBnum; i++)
        snowball[i].render(window);

    for (int i = 0; i < projectile_count; i++)
        projectile[i]->draw(window);

    for (int i = 0; i < dropCount; i++)
        drops[i]->draw(window);

    starEvent.draw_star(window);
    starEvent.draw_types(window);

    if (starEvent.get_showing_types())
    {
        bool mouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (mouseDown && !wasMousePressed)
        {
            sf::Vector2i pixel = sf::Mouse::getPosition(window);
            sf::Vector2f world = window.mapPixelToCoords(pixel);
            starEvent.handle_click(world, players[0]);
            wasMousePressed = true;
        }
        else if (!mouseDown)
            wasMousePressed = false;
    }

    renderGems(window);
    hud.draw(window);
}

playState::~playState()
{
    for (int i = 0; i < Enum; i++)
        delete enemies[i];
    for (int i = 0; i < dropCount; i++)
        delete drops[i];
    for (int p = 0; p < 2; p++)
        if (activePowerUp[p])
            delete activePowerUp[p];
}

int playState::getScore() { return score; }

void playState::spawnGemRain(int amount, bool isCash)
{
    gemCount = 0;
    isCashRain = isCash;
    if (isCash) cashTimer = 30.0f;
    for (int i = 0; i < amount && gemCount < MAX_GEMS; i++)
    {
        gemX[gemCount] = rand() % 700;
        gemY[gemCount] = 0;
        gemVelocity[gemCount] = 0;
        gemCollected[gemCount] = false;
        gemCount++;
    }
}

void playState::updateGems(float deltaTime)
{
    if (isCashRain) cashTimer -= deltaTime;
    for (int i = 0; i < gemCount; i++)
    {
        if (!gemCollected[i])
        {
            gemVelocity[i] += 0.05f;
            gemY[i] += gemVelocity[i];
            if (gemY[i] >= 650) gemY[i] = 650;
        }
    }
    if (isCashRain && cashTimer <= 0) gemCount = 0;
}

void playState::checkGemCollisions()
{
    for (int i = 0; i < gemCount; i++)
    {
        if (!gemCollected[i])
        {
            sf::FloatRect gemBounds(gemX[i], gemY[i], 15.0f, 15.0f);
            for (int p = 0; p < playerCount; p++)
            {
                sf::FloatRect playerBounds = players[p].getBounds();
                if (playerBounds.intersects(gemBounds))
                {
                    gemCollected[i] = true;
                    if (isCashRain)
                    {
                        players[p].addScore(500);
                        players[p].addGems(10);
                    }
                    else
                        players[p].addGems(1);
                    break;
                }
            }
        }
    }

    int writePos = 0;
    for (int i = 0; i < gemCount; i++)
    {
        if (!gemCollected[i])
        {
            gemX[writePos] = gemX[i];
            gemY[writePos] = gemY[i];
            gemVelocity[writePos] = gemVelocity[i];
            gemCollected[writePos] = gemCollected[i];
            writePos++;
        }
    }
    gemCount = writePos;
}

void playState::renderGems(sf::RenderWindow& window)
{
    for (int i = 0; i < gemCount; i++)
    {
        if (!gemCollected[i])
        {
            if (isCashRain)
            {
                sf::RectangleShape cash(sf::Vector2f(12.0f, 12.0f));
                cash.setPosition(gemX[i], gemY[i]);
                cash.setFillColor(sf::Color::Green);
                window.draw(cash);
            }
            else
            {
                sf::CircleShape gem(7.0f);
                gem.setPosition(gemX[i], gemY[i]);
                gem.setFillColor(sf::Color::Yellow);
                window.draw(gem);
            }
        }
    }
}

int playState::getLevel() { return level; }
void playState::setLevel(int lv) { level = lv; }
bool playState::setMultiplayer(bool mp) { return mp; }