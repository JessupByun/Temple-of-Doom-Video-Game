//
//  Scroll.h
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include "GameObject.h"
class Game;

#ifndef Scroll_h
#define Scroll_h

class Scroll : public GameObject {
public:
    //constructor and destructor
    Scroll(std::string name, Position* position);
    virtual ~Scroll();
    
    //action description function declaration
    virtual std::string actionDescription() const = 0;
    virtual void ability(Game& game) = 0;
    
    virtual int getBonusDexterity() const;
    virtual int getDamageAmount() const;

};

#endif /* Scroll_h */
