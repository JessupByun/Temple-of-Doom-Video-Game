//
//  DerivedScrolls.h
//  cs32project3
//
//  Created by Jessup Byun on 5/12/24.
//

#include "Scroll.h"
#include <string>
class Game;

#ifndef DerivedScrolls_h
#define DerivedScrolls_h

class Teleportation : public Scroll {
public:
    Teleportation(Position* position);
    virtual ~Teleportation();
        
    //action description function declaration
    virtual std::string actionDescription() const override;
    
    //ability function declaration
    virtual void ability(Game& game) override;
};


class ImproveArmor : public Scroll {
public:
    ImproveArmor(Position* position);
    virtual ~ImproveArmor();
    
    //action description function declaration
    virtual std::string actionDescription() const override;
    
    //ability function declaration
    virtual void ability(Game& game) override;
};


class RaiseStrength : public Scroll {
public:
    RaiseStrength(Position* position);
    virtual ~RaiseStrength();
    
    //action description function declaration
    virtual std::string actionDescription() const override;
    
    //ability function declaration
    virtual void ability(Game& game) override;
};


class EnhanceHealth : public Scroll {
public:
    EnhanceHealth(Position* position);
    virtual ~EnhanceHealth();
    
    //action description function declaration
    virtual std::string actionDescription() const override;
    
    //ability function declaration
    virtual void ability(Game& game) override;
};


class EnhanceDexterity : public Scroll {
public:
    EnhanceDexterity(Position* position);
    virtual ~EnhanceDexterity();
    
    //action description function declaration
    virtual std::string actionDescription() const override;
    
    //ability function declaration
    virtual void ability(Game& game) override;
};

#endif /* DerivedScrolls_h */
