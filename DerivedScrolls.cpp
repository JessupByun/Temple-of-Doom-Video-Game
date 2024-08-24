//
//  DerivedScrolls.cpp
//  cs32project3
//
//  Created by Jessup Byun on 5/12/24.
//

#include "Game.h"
#include "Player.h"
#include "utilities.h"
#include "DerivedScrolls.h"
using namespace std;

//Teleportation implementations
Teleportation::Teleportation(Position* position) : Scroll("scroll of teleportation", position) {}

Teleportation::~Teleportation() {}

string Teleportation::actionDescription() const {
    return "You read the scroll called scroll of teleportation\nYou feel your body wrenched in space and time.";
}

void Teleportation::ability(Game& game) {
    //give player a new set of coords
    bool playerLocationSet = false;
    while (playerLocationSet == false) {
        int x = randInt(1, 16);
        int y = randInt(1, 68);
        int playerX = game.getPlayer()->getPosition()->getXCoord();
        int playerY = game.getPlayer()->getPosition()->getYCoord();
        if (game.isMonsterAt(x, y) == true || game.isWallAt(x, y) == true) {
            continue;
        } else {
            game.getPlayer()->getPosition()->setX(x-playerX);
            game.getPlayer()->getPosition()->setY(y-playerY);
            playerLocationSet = true;
        }
    }
}

//ImproveArmor implementations

ImproveArmor::ImproveArmor(Position* position) : Scroll("scroll of improve armor", position) {}

ImproveArmor::~ImproveArmor() {}

string ImproveArmor::actionDescription() const {
    return "You read the scroll called scroll of improve armor!\nYour armor glows blue.";
}

void ImproveArmor::ability(Game& game) {
    int randomArmorIncrease = randInt(1,3);
    game.getPlayer()->setArmorPoints(randomArmorIncrease);
}

//RaiseStrength implementations

RaiseStrength::RaiseStrength(Position* position) : Scroll("scroll of raise strength", position) {}

RaiseStrength::~RaiseStrength() {}

string RaiseStrength::actionDescription() const {
    return "You read the scroll called scroll of raise strength\nYour muscles bulge.";
}

void RaiseStrength::ability(Game& game) {
    int randomStrengthIncrease = randInt(1,3);
    game.getPlayer()->setStrengthPoints(randomStrengthIncrease);
}

//EnhanceHealth implementations

EnhanceHealth::EnhanceHealth(Position* position) : Scroll("scroll of enhance health", position) {}

EnhanceHealth::~EnhanceHealth() {}

string EnhanceHealth::actionDescription() const {
    return "You read the scroll called scroll of enhance health!\nYou feel your heart beating stronger.";
}

void EnhanceHealth::ability(Game& game) {
    int randomMaxHealthIncrease = randInt(3,8);
    game.getPlayer()->setMaxHealth(game.getPlayer()->getMaxHealth() + randomMaxHealthIncrease);
}

//EnhanceDexterity implementations

EnhanceDexterity::EnhanceDexterity(Position* position) : Scroll("scroll of enhance dexterity", position) {}

EnhanceDexterity::~EnhanceDexterity() {}

string EnhanceDexterity::actionDescription() const {
    return "You read the scroll called scroll of enhance dexterity!\nYou feel like less of a klutz.";
}

void EnhanceDexterity::ability(Game& game) {
    game.getPlayer()->setDexterityPoints(1);
}
