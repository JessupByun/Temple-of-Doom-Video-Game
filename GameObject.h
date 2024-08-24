//
//  GameObject.h
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include "Position.h"
#include <string>
class Game;

#ifndef GameObject_h
#define GameObject_h

class GameObject 
{
public:
    //constructor and destructor
    GameObject(std::string name, Position* position);
    virtual ~GameObject();
    
    //pure virtual actionDescription function
    virtual std::string actionDescription() const = 0;
    virtual void ability(Game& game) = 0;
    
    //getters
    std::string getName();
    Position* getPosition() const;
    virtual int getBonusDexterity() const = 0;
    virtual int getDamageAmount() const = 0;

private:
    std::string m_name;
    Position* m_position;
};

#endif /* GameObject_h */
