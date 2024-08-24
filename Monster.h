//
//  Monster.h
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include <string>
#include "Actor.h"
class Game;

#ifndef Monster_h
#define Monster_h

class Monster : public Actor {
public:
    //constructor and destructor
    Monster(std::string name, Position* position, Weapon* weapon, int hitPoints, int strength, int dexterity, int armor, int sleep);
    virtual ~Monster();
    bool canMoveTo(Position* position, Game& game) const;

    //virtual function
    virtual bool turn(Game& game) = 0;
    
    //getter
    std::string getName() const;
    
private:
    std::string m_name;
};

#endif /* Monster_h */
