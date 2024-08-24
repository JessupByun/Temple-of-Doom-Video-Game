//
//  Player.h
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include "Actor.h"
#include "Scroll.h"
#include <vector>
class Game;

#ifndef Player_h
#define Player_h

class Player : public Actor {
public:
    //constructor and destructor
    Player(Position* position);
    virtual ~Player();
    
    //player's special actions and functions
    bool turn(char ch, Game& game);
    bool canMoveTo(Position* position, Game& game) const;
    void move(int xChange, int yChange, Game& game);
    
    bool pickUpObject(GameObject* item, Game& game); //adds item to the inventory
    void readScroll(char scrollLabel, Game& game); //must also remove the item from inventory (index is the index of the scroll in the inventory)
    void displayInventory() const;
    void wieldWeapon(char weaponLabel, Game& game);

    //getter functions
    std::vector<GameObject*>& getInventory();    
    
private:
    std::vector<GameObject*> m_inventory;
};

#endif /* Player_h */
