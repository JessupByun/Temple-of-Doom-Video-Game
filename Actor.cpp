//
//  Actor.cpp
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include <iostream>
#include "Actor.h"
#include "Game.h"
#include "utilities.h"
#include "DerivedWeapons.h"
using namespace std;

Actor::Actor(Position* position, Weapon* weapon, int hitPoints, int strength, int dexterity, int armor, int sleep) : m_position(position), m_currentWeapon(weapon), m_hitPoints(hitPoints), m_strengthPoints(strength), m_dexterityPoints(dexterity), m_armorPoints(armor), m_sleepTime(sleep) {
    maxHealth = hitPoints;
}

Actor::~Actor() {
    delete m_position;
    delete m_currentWeapon;
}

bool Actor::attack(Actor& defender) {
    int attackerPoints = getDexterityPoints() + getCurrentWeapon()->getBonusDexterity();
    int defenderPoints = defender.getCurrentWeapon()->getBonusDexterity() + defender.getArmorPoints();
    int damagePoints = randInt(0, getStrengthPoints() + getCurrentWeapon()->getDamageAmount() - 1);
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) { //random chance of hitting the defender given both sides' stats
        defender.setHitPoints(-damagePoints);
        return true;
    }
    return false; //if the attack missed
}

bool Actor::sleepMagicFang(Actor &defender) {
    //implement magic fang special case
    if (getCurrentWeapon()->getName() == "magic fangs of sleep") {
        int sleepChance = randInt(1,5);
        if (sleepChance == 1) {
            int sleepTime = randInt(2,6);
            if (sleepTime > m_sleepTime) {
                defender.setSleepTime(sleepTime);
            }
            return true;
        }
    }
    return false;
}

//getter functions
int Actor::getHitPoints() const {
    return m_hitPoints;
}

int Actor::getDexterityPoints() const {
    return m_dexterityPoints;
}

int Actor::getArmorPoints() const {
    return m_armorPoints;
}

int Actor::getStrengthPoints() const {
    return m_strengthPoints;
}

int Actor::getSleepTime() const {
    return m_sleepTime;
}

Position* Actor::getPosition() const {
    return m_position;
}

GameObject* Actor::getCurrentWeapon() const {
    return m_currentWeapon;
}

int Actor::getMaxHealth() const {
    return maxHealth;
}

//setter functions
void Actor::setHitPoints(int hpChange) {
    if(m_hitPoints+hpChange > 99) {
        m_hitPoints = 99;
    } else {
        m_hitPoints += hpChange;
    }
}

void Actor::setSleepTime(int sleepTime){
    m_sleepTime = sleepTime;
}

void Actor::setArmorPoints(int armorChange) {
    if(m_armorPoints+armorChange > 99) {
        m_armorPoints = 99;
    } else {
        m_armorPoints += armorChange;
    }
}

void Actor::setStrengthPoints(int strengthChange) {
    if(m_strengthPoints+strengthChange > 99) {
        m_strengthPoints = 99;
    } else {
        m_strengthPoints += strengthChange;
    }
}

void Actor::setDexterityPoints(int dexterityChange) {
    if(m_dexterityPoints+dexterityChange > 99) {
        m_dexterityPoints = 99;
    } else {
        m_dexterityPoints += dexterityChange;
    }
}

void Actor::setCurrentWeapon(GameObject* weapon) {
    m_currentWeapon = weapon;
}

void Actor::setMaxHealth(int maxHitpoints) {
    if (maxHitpoints > 99) {
        maxHealth = 99;
    } else {
        maxHealth = maxHitpoints;
    }
}

void Actor::setHitPointsAbsolute(int maxHitPoints) {
    if (maxHitPoints > 99) {
        m_hitPoints = 99;
    } else {
        m_hitPoints = maxHitPoints;
    }
}
