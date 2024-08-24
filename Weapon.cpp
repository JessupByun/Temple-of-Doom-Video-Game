//
//  Weapon.cpp
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include "Weapon.h"
using namespace std;

//constructor and destructor
Weapon::Weapon(string name, Position* position, int damage, int bonusDexterity) : GameObject(name, position), m_damage(damage), m_bonusDexterity(bonusDexterity) {}

Weapon::~Weapon() {}

//getter functions

int Weapon::getBonusDexterity() const
{
    return m_bonusDexterity;
}

int Weapon::getDamageAmount() const
{
    return m_damage;
}
