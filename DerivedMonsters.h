//
//  DerivedMonsters.h
//  cs32project3
//
//  Created by Jessup Byun on 5/12/24.
//

#include "Monster.h"

#ifndef DerivedMonsters_h
#define DerivedMonsters_h

class Bogeymen : public Monster {
public:
    Bogeymen(Position* position);
    virtual ~Bogeymen();
    virtual bool turn(Game& game) override;
    bool move(Game& game);
};

class Snakewomen : public Monster {
public:
    Snakewomen(Position* position);
    virtual ~Snakewomen();
    virtual bool turn(Game& game) override;
    bool move(Game& game);
};

class Dragons : public Monster {
public:
    Dragons(Position* position);
    virtual ~Dragons();
    virtual bool turn(Game& game) override;
};

class Goblins : public Monster {
public:
    Goblins(Position* position);
    virtual ~Goblins();
    int smellPlayer(int playerX, int playerY, int goblinX, int goblinY, int smellDistance, Game& game);
    bool move(Game& game);
    virtual bool turn(Game& game) override;
};

#endif /* DerivedMonsters_h */
