//
//  Weapon.h
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include "GameObject.h"

#ifndef Weapon_h
#define Weapon_h

class Weapon : public GameObject {
public:
    //constructor and destructor
    Weapon(std::string name, Position* position, int damage, int bonusDexterity);
    virtual ~Weapon();
    
    //pure virtual function for derived weapon action descriptions
    virtual std::string actionDescription() const = 0;
    virtual void ability(Game& game) = 0;

    //getter functions
    virtual int getBonusDexterity() const;
    virtual int getDamageAmount() const;
    
private:
    int m_damage;
    int m_bonusDexterity;
};

#endif /* Weapon_h */
