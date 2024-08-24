//
//  Monster.cpp
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include <iostream>
#include "Game.h"
#include "Monster.h"
#include "utilities.h"
#include "Player.h"
using namespace std;

Monster::Monster(string name, Position* position, Weapon* weapon, int hitPoints, int strength, int dexterity, int armor, int sleep) : Actor(position, weapon, hitPoints, strength, dexterity, armor, sleep), m_name(name) {}

Monster::~Monster() {}

bool Monster::canMoveTo(Position* position, Game& game) const { //helper function
    if (game.isValidCoord(position) == false) {
            return false;
    }
    //if there is a wall return false
    if (game.getMapChar(position) == '#') {
        return false;
    }
    //if the player is at that position return false
    if (game.getPlayer()->getPosition()->getXCoord() == position->getXCoord() && game.getPlayer()->getPosition()->getYCoord() == position->getYCoord()){
        return false;
    }
    //if there is another monster there at that position return false
    const vector<Monster*>& monsters = game.getMonsters();
    for (int i = 0; i < monsters.size(); i++) {
        if (monsters[i]->getPosition()->getXCoord() == position->getXCoord() && monsters[i]->getPosition()->getYCoord() == position->getYCoord()) {
            return false;
        }
    }
    return true; //default return if it is a valid space to move into
}

string Monster::getName() const {
    return m_name;
}
