//
//  Player.cpp
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include <iostream>
#include "Player.h"
#include "DerivedWeapons.h"
#include "utilities.h"
#include "Game.h"
#include "Monster.h"
using namespace std;

//constructor and destructor
Player::Player(Position* position) : Actor(position, new ShortSword(position), 20, 2, 2, 2, 0) {
    m_inventory.push_back(getCurrentWeapon());
}

Player::~Player() {}
        

bool Player::turn(char ch, Game& game) {
    if (ch == 'q') { //quit the game
        return true;
    }
    if (getHitPoints() <= 0) {
        return true;
    }
    //check if player is sleeping, if yes: do nothing
    if (getSleepTime() > 0) {
        setSleepTime(getSleepTime()-1);
        return false;
    }
    //1 in 10 chance of increasing health by 1 up to maxhealth
    int healthIncrease = randInt(1,10);
    if (healthIncrease == 1 && getHitPoints() < getMaxHealth()) {
        setHitPoints(healthIncrease);
    }
    //rest of player's input commands (if it doesn't match one of these, do nothing)
    if (ch == 'g') { //pick up an object only if there is an object there
        //check if the goldenidol is there
        if (game.getPlayer()->getPosition()->getXCoord() == game.getIdolPosition()->getXCoord() && game.getPlayer()->getPosition()->getYCoord() == game.getIdolPosition()->getYCoord()) {
            string message1 = "You pick up the golden idol";
            string message2 = "Congratulations, you won!";
            game.getMessages().push_back(message1);
            game.getMessages().push_back(message2);
            clearScreen();
            game.display();
            return true;
        }
        vector<GameObject*> items = game.getItems();
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->getPosition()->getXCoord() == getPosition()->getXCoord() && items[i]->getPosition()->getYCoord() == getPosition()->getYCoord()) { //check if there is a weapon/scroll/goldenidol at that position
                for (int i = 0; i < game.getItems().size(); i++) {
                    if (game.getItems().at(i)->getPosition()->getXCoord() == game.getPlayer()->getPosition()->getXCoord() && game.getItems().at(i)->getPosition()->getYCoord() == game.getPlayer()->getPosition()->getYCoord()) { //if you found the object being picked up in the items vector
                        GameObject* item = game.getItems().at(i);
                        if (game.getPlayer()->pickUpObject(item, game) == false) { //add item to inventory and return false because game did not end
                            return false;
                        }
                    }
                }
            }
        }
    }
    else if (ch == 'c') {
        setMaxHealth(50);
        setHitPointsAbsolute(50);
        setStrengthPoints(9-getStrengthPoints());
    }
    else if (ch == ARROW_UP || ch == ARROW_DOWN || ch == ARROW_LEFT || ch == ARROW_RIGHT) { //player moves
        switch(ch) {
            case ARROW_UP:
                move(-1,0, game);
                break;
            case ARROW_DOWN:
                move(1,0, game);
                break;
            case ARROW_LEFT:
                move(0,-1, game);
                break;
            case ARROW_RIGHT:
                move(0,1, game);
                break;
        }
    }
    return false;
}

//player functions
void Player::move(int xChange, int yChange, Game& game) { //implement attack in move
    Position* futurePosition = new Position(getPosition()->getXCoord()+xChange, getPosition()->getYCoord()+yChange); //create a position object of where the player is trying to move into
    if (canMoveTo(futurePosition, game) == true) { //if the player can move to the space, edit position
        getPosition()->setX(xChange);
        getPosition()->setY(yChange);
    }
    const vector<Monster*>& monsters = game.getMonsters();
    for (int i = 0; i < monsters.size(); i++) {
        Monster* defender = monsters[0]; //initialize to monsters[0] for now, will get overriden
        if (monsters[i]->getPosition()->getXCoord() == futurePosition->getXCoord() && monsters[i]->getPosition()->getYCoord() == futurePosition->getYCoord()) {  //if player moves towards monster -> attack the monster
            string monsterName = monsters[i]->getName();
            defender = monsters[i];
            string attackDescription1 = "Player " + getCurrentWeapon()->actionDescription();
            string attackDescription2;
            string finalMessage;
            if (attack(*defender) == true) { //if the attack hit (simulatanously attacks the defender and alters hp)
                if (defender->getHitPoints() <= 0) { //if the attack killed the monster
                    attackDescription2 = monsterName + " dealing a final blow.";
                } else { //if the monster survived
                    if (getCurrentWeapon() )
                    attackDescription2 = monsterName + " and hits.";
                }
            } else { // if the attack missed
                attackDescription2 = monsterName + " and misses.";
            }
            if (sleepMagicFang(*defender) == true) { //attempt to sleep with magic fang, if it does sleep the monster, then change the actiondescription string to say it slept the monster
                attackDescription2 = " and hits, putting " + monsterName + " to sleep.";
            }
            finalMessage = attackDescription1 + attackDescription2;
            game.getMessages().push_back(finalMessage);
        }
    }
}

bool Player::canMoveTo(Position* position, Game& game) const { //helper function
    if (game.isValidCoord(position) == false) {
        return false;
    }
    if (game.getMapChar(position) == '#') {
        return false;
    }
    const vector<Monster*>& monsters = game.getMonsters();
    for (int i = 0; i < monsters.size(); i++) {
        if (monsters[i]->getPosition()->getXCoord() == position->getXCoord() && monsters[i]->getPosition()->getYCoord() == position->getYCoord()) {
            return false;
        }
    }
    return true; //default return (if there aren't other monsters on the
}

bool Player::pickUpObject(GameObject* item, Game& game) { //add item to inventory
    if (m_inventory.size() <= 25) { //max inventory size is 26
        m_inventory.push_back(item);
        vector<GameObject*>& items = game.getItems();
        char itemInitial = ' ';
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->getPosition()->getXCoord() == getPosition()->getXCoord() && items[i]->getPosition()->getYCoord() == getPosition()->getYCoord()) { //check if there is a weapon/scroll/goldenidol at that position
                string itemName = items[i]->getName();
                if (itemName == "mace" || itemName == "long sword" || itemName == "short sword" || itemName == "magic fangs of sleep" || itemName == "magic axe") {
                    itemInitial = ')';
                }
                else if (itemName == "scroll of enhance dexterity" || itemName == "scroll of improve armor" || itemName == "scroll of raise strength" || itemName == "scroll of enhance health" || itemName == "scroll of teleportation") {
                    itemInitial = '?';
                }
            }
        }
        string message = "\0";
        switch(itemInitial) {
            case '?':
                message = "You pick up a scroll called " + item->getName() + "!";
                game.getMessages().push_back(message);
                break;
            case ')':
                message = "You pick up " + item->getName() + "!";
                game.getMessages().push_back(message);
                break;
        }
        //delete the object from m_items and then erase the pointer that used to point to the item
        for (int i = 0; i < game.getItems().size(); i++) { //find the item's index in m_items
            if (game.getItems().at(i)->getPosition()->getXCoord() == item->getPosition()->getXCoord() && game.getItems().at(i)->getPosition()->getYCoord() == item->getPosition()->getYCoord()) {
                game.getItems().erase(game.getItems().begin() + i);
            }
        }
    }
    else {
        string message = "Your knapsack is full; you can't pick that up.";
        game.getMessages().push_back(message);
    }
    return false;
}

void Player::wieldWeapon(char weaponLabel, Game& game) {
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int itemIndex = 0;
    for (int i = 0; i < 26; i++) { //convert the letter to number
        if (letters[i] == weaponLabel) {
            itemIndex = i;
        }
    }
    if (getInventory().size() > itemIndex) {
        string name = getInventory().at(itemIndex)->getName(); //get the name of the weapon/scroll player is attempting to wield
        string message = "\0";
        if (name == "mace" || name == "short sword" || name == "long sword" || name == "magic axe" || name == "magic fangs of sleep") { //if it is a weapon
            setCurrentWeapon(getInventory().at(itemIndex)); //make your current weapon pointer point to the weapon
            message = "You are wielding " + name;
            game.getMessages().push_back(message);
        }
        else { //if it's a scroll
            message = "You can't wield " + name;
            game.getMessages().push_back(message);
        }
    }
}

void Player::readScroll(char scrollLabel, Game& game) {
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int itemIndex = 30;
    for (int i = 0; i < 26; i++) { //convert the letter to number
        if (letters[i] == scrollLabel) {
            itemIndex = i;
        }
    }
    if (getInventory().size() > itemIndex) { //check for out of bounds (read scroll only if the letter is valid and is a scroll)
        string name = getInventory().at(itemIndex)->getName(); //get the name of the weapon/scroll player is attempting to wield
        string message = "\0";
        if (name == "scroll of teleportation" || name == "scroll of improve armor" || name == "scroll of enhance health" || name == "scroll of enhance dexterity" || name == "scroll of raise strength") { //if it is a scroll
            //use the scroll's ability and push back the scroll's action message
            getInventory().at(itemIndex)->ability(game);
            message = getInventory().at(itemIndex)->actionDescription();
            game.getMessages().push_back(message);
            //delete the scroll and then erase the pointer that used to point to the scroll
            getInventory().erase(getInventory().begin() + itemIndex);
        } 
        else { //if item selected exists but it's a weapon
            message = "You can't read a " + name;
            game.getMessages().push_back(message);
        }
    }
}

void Player::displayInventory() const {
    cout << "Inventory:" << endl;
    char label = 'a';
    for (int i = 0; i < m_inventory.size(); i++) {
        if (m_inventory[i]) {//check if the pointer is not nullptr
            string itemName = m_inventory[i]->getName();
            //if item is a scroll
            if (itemName == "scroll of teleportation" || itemName == "scroll of enhance health" || itemName == "scroll of enhance dexterity" || itemName == "scroll of improve armor" || itemName == "scroll of raise strength") {
                cout << " " << label++ << ". A scroll called " << m_inventory[i]->getName() << endl;
            }
            //if item is a weapon
            else if (itemName == "mace" || itemName == "magic fangs of sleep" || itemName == "short sword" || itemName == "long sword" || itemName == "magic axe") {
                cout << " " << label++ << ". " << m_inventory[i]->getName() << endl;
            }
        }
    }
}

//getter functions
vector<GameObject*>& Player::getInventory() {
    return m_inventory;
}

