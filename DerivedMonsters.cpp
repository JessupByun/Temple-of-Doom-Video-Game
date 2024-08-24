//
//  DerivedMonsters.cpp
//  cs32project3
//
//  Created by Jessup Byun on 5/12/24.
//

#include <iostream>
#include "Game.h"
#include "Player.h"
#include "DerivedMonsters.h"
#include "DerivedWeapons.h"
#include "DerivedScrolls.h"
#include "utilities.h"
#include <algorithm>

using namespace std;

//Bogeymen implementation
Bogeymen::Bogeymen(Position* position) : Monster("Bogeyman", position, new ShortSword(position), randInt(5, 10), randInt(2,3), randInt(2,3), 2, 0) {}

Bogeymen::~Bogeymen() {}

bool Bogeymen::move(Game& game) {
    int playerXCoord = game.getPlayer()->getPosition()->getXCoord();
    int playerYCoord = game.getPlayer()->getPosition()->getYCoord();
    int bogeymanXCoord = this->getPosition()->getXCoord();
    int bogeymanYCoord = this->getPosition()->getYCoord();
    
    int xDifference = playerXCoord - bogeymanXCoord;
    int yDifference = playerYCoord - bogeymanYCoord;
    int distance = abs(xDifference) + abs(yDifference);
    
    if (distance <= 5) { //if bogeymen is within range
        Position* rightPosition = new Position(bogeymanXCoord+1, bogeymanYCoord);
        Position* leftPosition = new Position(bogeymanXCoord-1, bogeymanYCoord);
        Position* upPosition = new Position(bogeymanXCoord, bogeymanYCoord+1);
        Position* downPosition = new Position(bogeymanXCoord, bogeymanYCoord-1);
        
        //move in a direction if there is distance between the bogeymen and the player and it can move to that position
        if (xDifference > 0 && canMoveTo(rightPosition, game)) {
            this->getPosition()->setX(1);
        }
        else if (xDifference < 0 && canMoveTo(leftPosition, game)) {
            this->getPosition()->setX(-1);
        }
        else if (yDifference > 0 && canMoveTo(upPosition, game)) {
            this->getPosition()->setY(1);
        }
        else if (yDifference < 0 && canMoveTo(downPosition, game)) {
            this->getPosition()->setY(-1);
        }
        else if ((rightPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && rightPosition->getYCoord() == game.getPlayer()->getPosition()->getYCoord()) || (leftPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && leftPosition->getYCoord() == game.getPlayer()->getPosition()->getYCoord()) || (upPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && upPosition->getYCoord() == game.getPlayer()->getPosition()->getYCoord()) || (downPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && downPosition->getYCoord() == game.getPlayer()->getPosition()->getYCoord())) { //if the monster next to player, attack the player
            string attackDescription1 = "the " + getName() + " " + getCurrentWeapon()->actionDescription();
            string attackDescription2;
            string finalMessage;
            Actor* defender = game.getPlayer();
            if (attack(*defender) == true) { //if the attack hit (simulatanously attacks the defender and alters hp)
                if (defender->getHitPoints() <= 0) { //if the attack killed the player
                    attackDescription2 = "Player dealing a final blow.";
                    finalMessage = attackDescription1 + attackDescription2;
                    game.getMessages().push_back(finalMessage);
                    delete rightPosition;
                    delete leftPosition;
                    delete upPosition;
                    delete downPosition;
                    return true;
                } else { //if the player survived
                    if (getCurrentWeapon() )
                    attackDescription2 = "Player and hits.";
                }
            } else { // if the attack missed
                attackDescription2 = "Player and misses.";
            }
            finalMessage = attackDescription1 + attackDescription2;
            game.getMessages().push_back(finalMessage);
        }
        delete rightPosition;
        delete leftPosition;
        delete upPosition;
        delete downPosition;
    }
    return false;
}

bool Bogeymen::turn(Game& game) {
    //if health is = 0, drop item
    if (getHitPoints() <= 0) {
        //drop item (1 in 10 chance)
        int dropItem = randInt(1,10);
        vector<GameObject*>& items = game.getItems();
        bool itemAlreadyPresent = false;
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->getPosition() == getPosition()) {
                itemAlreadyPresent = true;
            }
        }
        if (dropItem == 1 && itemAlreadyPresent == false) { //drop the item if 1/3 chance is true and no item present already
            Position* position = new Position(getPosition()->getXCoord(), getPosition()->getYCoord());
            GameObject* newItem = new MagicAxe(position);
            game.getItems().push_back(newItem);
        }
         
        //remove the monster from the game
        vector<Monster*>& monsters = game.getMonsters();
        for (int i = 0; i < game.getMonsters().size(); i++) {
            if (monsters[i]->getPosition() == getPosition()) { //if you found the monster that died in the vector
                game.getMonsters().erase(game.getMonsters().begin() + i); // remove the monster from the vector
            }
        }
    }
    if (getSleepTime() > 0) {
        setSleepTime(getSleepTime()-1);
        return false; //exit function
    }
    if (move(game) == true) {
        return true; //return true if move returned true which means player was killed
    }
    return false;
}

//Snakewomen implementation

Snakewomen::Snakewomen(Position* position) : Monster("Snakewoman", position, new MagicFang(position), randInt(3, 6), 2, 3, 3, 0) {}

Snakewomen::~Snakewomen() {}

bool Snakewomen::move(Game& game) {
    int playerXCoord = game.getPlayer()->getPosition()->getXCoord();
    int playerYCoord = game.getPlayer()->getPosition()->getYCoord();
    int snakewomenXCoord = this->getPosition()->getXCoord();
    int snakewomenYCoord = this->getPosition()->getYCoord();
    
    int xDifference = playerXCoord - snakewomenXCoord;
    int yDifference = playerYCoord - snakewomenYCoord;
    int distance = abs(xDifference) + abs(yDifference);
    
    if (distance <= 3) {
        Position* rightPosition = new Position(snakewomenXCoord+1, snakewomenYCoord);
        Position* leftPosition = new Position(snakewomenXCoord-1, snakewomenYCoord);
        Position* upPosition = new Position(snakewomenXCoord, snakewomenYCoord+1);
        Position* downPosition = new Position(snakewomenXCoord, snakewomenYCoord-1);
        
        if (xDifference > 0 && canMoveTo(rightPosition, game)) {
            this->getPosition()->setX(1);
        }
        else if (xDifference < 0 && canMoveTo(leftPosition, game)) {
            this->getPosition()->setX(-1);
        }
        else if (yDifference > 0 && canMoveTo(upPosition, game)) {
            this->getPosition()->setY(1);
        }
        else if (yDifference < 0 && canMoveTo(downPosition, game)) {
            this->getPosition()->setY(-1);
        }
        else if ((rightPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && rightPosition->getYCoord() == game.getPlayer()->getPosition()->getYCoord()) || (leftPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && leftPosition->getYCoord() == game.getPlayer()->getPosition()->getYCoord()) || (upPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && upPosition->getYCoord() == game.getPlayer()->getPosition()->getYCoord()) || (downPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && downPosition->getYCoord() == game.getPlayer()->getPosition()->getYCoord())) { //if the monster next to player, attack the player
            string attackDescription1 = "the " + getName() + " " + getCurrentWeapon()->actionDescription();
            string attackDescription2;
            string finalMessage;
            Actor* defender = game.getPlayer();
            if (attack(*defender) == true) { //if the attack hit (simulatanously attacks the defender and alters hp)
                if (defender->getHitPoints() <= 0) { //if the attack killed the player
                    attackDescription2 = "Player dealing a final blow.";
                    finalMessage = attackDescription1 + attackDescription2;
                    game.getMessages().push_back(finalMessage);
                    delete rightPosition;
                    delete leftPosition;
                    delete upPosition;
                    delete downPosition;
                    return true;
                } else { //if the player survived
                    if (getCurrentWeapon() )
                    attackDescription2 = "Player and hits.";
                }
            } else { // if the attack missed
                attackDescription2 = "Player and misses.";
            }
            if (sleepMagicFang(*defender) == true) { //attempt to sleep with magic fang, if it does sleep the player, then change the actiondescription string to say it slept the player
                attackDescription2 = "Player and hits, putting Player to sleep.";
            }
            finalMessage = attackDescription1 + attackDescription2;
            game.getMessages().push_back(finalMessage);
        }
        delete rightPosition;
        delete leftPosition;
        delete upPosition;
        delete downPosition;
    }
    return false;
}

bool Snakewomen::turn(Game& game) {
    //if health is = 0 monster dies and drops item
    if (getHitPoints() <= 0) {
        //drop item (1 in 3 chance)
        int dropItem = randInt(1,3);
        vector<GameObject*>& items = game.getItems();
        bool itemAlreadyPresent = false;
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->getPosition() == getPosition()) {
                itemAlreadyPresent = true;
            }
        }
        if (dropItem == 1 && itemAlreadyPresent == false) { //drop the item if 1/3 chance is true and no item present already
            Position* position = new Position(getPosition()->getXCoord(), getPosition()->getYCoord());
            GameObject* newItem = new MagicFang(position);
            game.getItems().push_back(newItem);
        }
         
        //remove the monster from the game
        vector<Monster*>& monsters = game.getMonsters();
        for (int i = 0; i < game.getMonsters().size(); i++) {
            if (monsters[i]->getPosition() == getPosition()) { //if you found the monster that died in the vector
                game.getMonsters().erase(game.getMonsters().begin() + i); // remove the monster from the vector
            }
        }
    }
    if (getSleepTime() > 0) {
        setSleepTime(getSleepTime()-1);
        return false; //exit function
    }
    if (move(game) == true) {
        return true; //return true if move returned true which means player was killed
    }
    return false;
}

//Dragons implementation

Dragons::Dragons(Position* position) : Monster("Dragon", position, new LongSword(position), randInt(20, 25), 4, 4, 4, 0) {}

Dragons::~Dragons() {}

bool Dragons::turn(Game& game) {
    //if health is = 0, drop item
    if (getHitPoints() <= 0) {
        vector<GameObject*>& items = game.getItems();
        bool itemAlreadyPresent = false;
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->getPosition() == getPosition()) {
                itemAlreadyPresent = true;
            }
        }
        if (itemAlreadyPresent == false) { //drop the item if no item present already (100% chance of scroll drop)
            Position* position = new Position(getPosition()->getXCoord(), getPosition()->getYCoord());
            GameObject* newItem;
            int scroll = randInt(1,5);
            switch (scroll) {
                case 1:
                    newItem = new Teleportation(position);
                    break;
                case 2:
                    newItem = new RaiseStrength(position);
                    break;
                case 3:
                    newItem = new EnhanceHealth(position);
                    break;
                case 4:
                    newItem = new EnhanceDexterity(position);
                    break;
                case 5:
                    newItem = new ImproveArmor(position);
                    break;
            }
            game.getItems().push_back(newItem);
        }
    
        //remove the monster from the game
        vector<Monster*>& monsters = game.getMonsters();
        for (int i = 0; i < game.getMonsters().size(); i++) {
            if (monsters[i]->getPosition() == getPosition()) { //if you found the monster that died in the vector
                game.getMonsters().erase(game.getMonsters().begin() + i); // remove the monster from the vector
            }
        }
    }
    //if dragon is asleep
    if (getSleepTime() > 0) {
        setSleepTime(getSleepTime()-1);
        return false;
    }
    
    //1 in 10 chance of increasing health by 1 up to maxhealth
    int healthIncrease = randInt(1,10);
    if (healthIncrease == 1 && getHitPoints() < getMaxHealth()) {
        setHitPoints(healthIncrease);
    }
    
    //attack the player
    int dragonXCoord = this->getPosition()->getXCoord();
    int dragonYCoord = this->getPosition()->getYCoord();
    
    Position* rightPosition = new Position(dragonXCoord+1, dragonYCoord);
    Position* leftPosition = new Position(dragonXCoord-1, dragonYCoord);
    Position* upPosition = new Position(dragonXCoord, dragonYCoord+1);
    Position* downPosition = new Position(dragonXCoord, dragonYCoord-1);
        
       
    if ((rightPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && rightPosition->getYCoord() == game.getPlayer()->getPosition()->getYCoord()) || (leftPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && leftPosition->getYCoord() == game.getPlayer()->getPosition()->getYCoord()) || (upPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && upPosition->getYCoord() == game.getPlayer()->getPosition()->getYCoord()) || (downPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && downPosition->getYCoord() == game.getPlayer()->getPosition()->getYCoord())) { //if the monster next to player, attack the player
        string attackDescription1 = "the " + getName() + " " + getCurrentWeapon()->actionDescription();
        string attackDescription2;
        string finalMessage;
        Actor* defender = game.getPlayer();
        if (attack(*defender) == true) { //if the attack hit (simulatanously attacks the defender and alters hp)
            if (defender->getHitPoints() <= 0) { //if the attack killed the player
                attackDescription2 = "Player dealing a final blow.";
                finalMessage = attackDescription1 + attackDescription2;
                game.getMessages().push_back(finalMessage);
                delete rightPosition;
                delete leftPosition;
                delete upPosition;
                delete downPosition;
                return true;
            } else { //if the player survived
                if (getCurrentWeapon() )
                attackDescription2 = "Player and hits.";
            }
        } else { // if the attack missed
            attackDescription2 = "Player and misses.";
        }
        finalMessage = attackDescription1 + attackDescription2;
        game.getMessages().push_back(finalMessage);
    }
    delete rightPosition;
    delete leftPosition;
    delete upPosition;
    delete downPosition;
    return false;
}

//Goblins implementation

Goblins::Goblins(Position* position) : Monster("Goblin", position, new ShortSword(position), randInt(15, 20), 3, 1, 1, 0) {}

Goblins::~Goblins() {}

//returns the shortest distance that the goblin can take to reach the player
int Goblins::smellPlayer(int playerX, int playerY, int goblinX, int goblinY, int smellDistance, Game& game) {
    if (playerX == goblinX && playerY == goblinY) {
        return 0; // Base case: player found (return distance which is 0)
    }
    Position* futurePosition = new Position(goblinX,goblinY);
    if (canMoveTo(futurePosition, game) == false) {
        return 20; // Base case: hit a wall or another monster
    }
    if (smellDistance <= 0) {
        return 20; // Base case: distance limit exceeded
    }
    if ((abs(playerX-goblinX) + abs(playerY-goblinY)) > smellDistance) {
        return 20;
    }
    int minDistance = 20;
    //find the real minDistance
    minDistance = min(smellPlayer(playerX, playerY, goblinX, goblinY+1, smellDistance-1, game), minDistance);
    minDistance = min(smellPlayer(playerX, playerY, goblinX, goblinY-1, smellDistance-1, game), minDistance);
    minDistance = min(smellPlayer(playerX, playerY, goblinX-1, goblinY, smellDistance-1, game), minDistance);
    minDistance = min(smellPlayer(playerX, playerY, goblinX+1, goblinY, smellDistance-1, game), minDistance);
                          
    return minDistance + 1; //if no path is found it returns 20+1
}

bool Goblins::move(Game& game) {
    int playerX = game.getPlayer()->getPosition()->getXCoord();
    int playerY = game.getPlayer()->getPosition()->getYCoord();
    int goblinX = getPosition()->getXCoord();
    int goblinY = getPosition()->getYCoord();
    int smellDistance = game.getGoblinSmellDistance();
    
    Position* rightPosition = new Position(goblinX+1, goblinY);
    Position* leftPosition = new Position(goblinX-1, goblinY);
    Position* upPosition = new Position(goblinX, goblinY+1);
    Position* downPosition = new Position(goblinX, goblinY-1);

    //if the monster next to player, attack the player
    if ((rightPosition->getXCoord() == playerX && rightPosition->getYCoord() == playerY) || (leftPosition->getXCoord() == playerX && leftPosition->getYCoord() == playerY) || (upPosition->getXCoord() == playerX && upPosition->getYCoord() == playerY) || (downPosition->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && downPosition->getYCoord() == playerY)) {
        string attackDescription1 = "the " + getName() + " " + getCurrentWeapon()->actionDescription();
        string attackDescription2;
        string finalMessage;
        Actor* defender = game.getPlayer();
        if (attack(*defender) == true) { //if the attack hit (simulatanously attacks the defender and alters hp)
            if (defender->getHitPoints() <= 0) { //if the attack killed the player
                attackDescription2 = "Player dealing a final blow.";
                finalMessage = attackDescription1 + attackDescription2;
                game.getMessages().push_back(finalMessage);
                delete rightPosition;
                delete leftPosition;
                delete upPosition;
                delete downPosition;
                return true;
            } else { //if the player survived
                if (getCurrentWeapon() )
                attackDescription2 = "Player and hits.";
            }
        } else { // if the attack missed
            attackDescription2 = "Player and misses.";
        }
        finalMessage = attackDescription1 + attackDescription2;
        game.getMessages().push_back(finalMessage);
        delete rightPosition;
        delete leftPosition;
        delete upPosition;
        delete downPosition;
        return false;
    }
    
    //if the goblin isn't right next to the player, smell the player and move
    int rightDistance = smellPlayer(playerX, playerY, goblinX, goblinY+1, smellDistance-1, game); //right
    int leftDistance = smellPlayer(playerX, playerY, goblinX, goblinY-1, smellDistance-1, game); //left
    int upDistance = smellPlayer(playerX, playerY, goblinX-1, goblinY, smellDistance-1, game); //up
    int downDistance = smellPlayer(playerX, playerY, goblinX+1, goblinY, smellDistance-1, game); //down
    
    //find the minDistance
    int minDistance;
    minDistance = min(leftDistance, rightDistance);
    minDistance = min(upDistance, minDistance);
    minDistance = min(downDistance, minDistance);
    
    //figure out which direction provided the minDistance
    if (minDistance > smellDistance) {
        return false;
    }
    if (minDistance == rightDistance) { //move right
        getPosition()->setY(1);
    }
    else if (minDistance == leftDistance) { //move left
        getPosition()->setY(-1);
    }
    else if (minDistance == upDistance) { //move up
        getPosition()->setX(-1);
    }
    else if (minDistance == downDistance) { //move down
        getPosition()->setX(1);
    }
    
    // if goblin tries to move into player, attack the player and if player dies return true
    return false; //player is still alive
}

bool Goblins::turn(Game& game) {
    //if health is = 0, drop item
    if (getHitPoints() <= 0) {
        //drop item (1 in 10 chance)
        int dropItem = randInt(1,3);
        vector<GameObject*>& items = game.getItems();
        bool itemAlreadyPresent = false;
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->getPosition() == getPosition()) {
                itemAlreadyPresent = true;
            }
        }
        if (dropItem == 1 && itemAlreadyPresent == false) { //drop either magic fang or magic axe if 1/3 chance is true and no item present already
            int itemType = randInt(1,2);
            Position* position = new Position(getPosition()->getXCoord(), getPosition()->getYCoord());
            if (itemType == 1) { //drop magic axe
                GameObject* newItem = new MagicAxe(position);
                game.getItems().push_back(newItem);
            }
            else if (itemType == 2) { //drop magic fangs of sleep
                GameObject* newItem = new MagicFang(position);
                game.getItems().push_back(newItem);
            }
        }
         
        //remove the monster from the game
        vector<Monster*>& monsters = game.getMonsters();
        for (int i = 0; i < game.getMonsters().size(); i++) {
            if (monsters[i]->getPosition() == getPosition()) { //if you found the monster that died in the vector
                game.getMonsters().erase(game.getMonsters().begin() + i); // remove the monster from the vector
            }
        }
    }
    //if goblin is asleep
    if (getSleepTime() > 0) {
        setSleepTime(getSleepTime()-1);
        return false; //exit function
    }
    if (move(game) == true) {
        return true; //return true if move returned true which means player was killed
    }
    return false;
}
