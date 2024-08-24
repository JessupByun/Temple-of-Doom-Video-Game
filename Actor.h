//
//  Actor.h
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include "Position.h"
class GameObject;
class Weapon;
class Game;

#ifndef Actor_h
#define Actor_h

class Actor
{
public:
    //constructor and destructor
    Actor(Position* position, Weapon* weapon, int hitPoints, int strength, int dexterity, int armor, int sleep);
    virtual ~Actor();
    
    //actor functions
    bool attack(Actor& defender);
    bool sleepMagicFang(Actor& defender);

    //getter functions
    int getHitPoints() const;
    int getDexterityPoints() const;
    int getArmorPoints() const;
    int getStrengthPoints() const;
    int getSleepTime() const;
    Position* getPosition() const;
    GameObject* getCurrentWeapon() const;
    int getMaxHealth() const;

    //setter functions
    void setHitPoints(int hpChange); //adds hpChange to actor's hitpoints (e.g. if hpChange is positive, hitpoints increases)
    void setHitPointsAbsolute(int hitpoints);
    void setSleepTime(int sleepTime); //doesn't add but instead sets sleeptime to whatever is passed in
    void setArmorPoints(int armorChange); //adds armoreChange to actor's armor points
    void setStrengthPoints(int strengthChange);
    void setDexterityPoints(int dexterityChange);
    void setCurrentWeapon(GameObject* weapon);
    void setMaxHealth(int maxHitPoints);
    
private:
    Position* m_position;
    GameObject* m_currentWeapon;
    int maxHealth;
    int m_hitPoints;
    int m_armorPoints;
    int m_dexterityPoints;
    int m_strengthPoints;
    int m_sleepTime;
};

#endif /* Actor_h */
