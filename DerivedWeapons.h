//
//  DerivedWeapons.h
//  cs32project3
//
//  Created by Jessup Byun on 5/12/24.
//

#include "Weapon.h"

#ifndef DerivedWeapons_h
#define DerivedWeapons_h

class Mace : public Weapon {
public:
    Mace(Position* position);
    virtual ~Mace();
    
    //action description function declaration
    virtual std::string actionDescription() const override;
    virtual void ability(Game& game) override; //leave empty

};


class ShortSword : public Weapon {
public:
    ShortSword(Position* position);
    virtual ~ShortSword();
    
    //action description function declaration
    virtual std::string actionDescription() const override;
    virtual void ability(Game& game) override; //leave empty
};


class LongSword : public Weapon {
public:
    LongSword(Position* position);
    virtual ~LongSword();
    
    //action description function declaration
    virtual std::string actionDescription() const override;
    virtual void ability(Game& game) override; //leave empty
};


class MagicAxe : public Weapon {
public:
    MagicAxe(Position* position);
    virtual ~MagicAxe();
    
    //action description function declaration
    virtual std::string actionDescription() const override;
    virtual void ability(Game& game) override; //leave empty
};


class MagicFang : public Weapon {
public:
    MagicFang(Position* position);
    virtual ~MagicFang();
    
    //action description function declaration
    virtual std::string actionDescription() const override;
    virtual void ability(Game& game) override; //leave empty
};

#endif /* DerivedWeapons_h */
