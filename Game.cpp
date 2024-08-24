//
//  Game.cpp
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include <iostream>
#include "Game.h"
#include "utilities.h"
#include "Actor.h"
#include "Player.h"
#include "DerivedMonsters.h"
#include "DerivedWeapons.h"
#include "DerivedScrolls.h"
#include "Position.h"
#include "Room.h"
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance) : m_goblinSmellDistance(goblinSmellDistance), m_level(0)
{
    m_stairwayPosition = new Position(0,0);
    m_idolPosition = new Position(0,0); //initialize to out of bounds for now (createlevel will override)
    createLevel(); //game starts with level 0 but helper function take care of level check
}

Game::~Game() {
    //delete monsters
    for (int i = 0; i < m_monsters.size(); i++) {
        delete m_monsters[i];
    }
    m_monsters.clear();
    
    //delete items and their positions
    for (int i = 0; i < m_items.size(); i++) {
        delete m_items[i]->getPosition();
        delete m_items[i];
    }
    m_items.clear();
    
    //delete player
    delete m_player;
    
    delete m_stairwayPosition;
    
    delete m_idolPosition;
}

void Game::play() {
    char ch = '0';
    clearScreen();
    display();
    while (ch != 'q') { //player's turn(s)'
        ch = getCharacter();

        //check if game ended after player's turn bc if they picked up the idol turn returns true if game over
        if (m_player->turn(ch, *this) == true) {
            break;
        }
        //monsters turn
        for (int i = 0; i < m_monsters.size(); i++) {
            if (m_monsters[i]->turn(*this) == true) { //check if game ended after monsters's turn bc if they killed the player the game ends
                break;
            }
        }
        
        //display inventory if w r or i
        if (ch == 'w') {
            clearScreen();
            m_player->displayInventory();
            char weaponLabel = getCharacter(); //read in character denoting weapon
            //wield weapon
            m_player->wieldWeapon(weaponLabel, *this);
            clearScreen();
            display();
        }
        else if (ch == 'r') {
            clearScreen();
            m_player->displayInventory();
            char scrollLabel = getCharacter(); //read in character denoting scroll
            //read scroll
            m_player->readScroll(scrollLabel, *this);
            clearScreen();
            display();
        }
        else if (ch == 'i') { //display inventory
            clearScreen();
            m_player->displayInventory();
        }
        //move onto next level
        else if (ch == '>' && (m_player->getPosition()->getXCoord() == getStairwayPosition()->getXCoord() && m_player->getPosition()->getYCoord() == getStairwayPosition()->getYCoord())) { //descend stairs, change level but technically same object still (only keep player)
            //increment level
            m_level += 1;
            
            //reset walls to empty and add new layout
            addWalls();
            
            //clear items vector and add items
            m_items.clear();
            addItems();
            
            //clear monsters vector and add items
            m_monsters.clear();
            addMonster();
            
            //add stairways or golden idol
            addStairwayOrGoldenIdol();
            
            //give player a new location
            bool playerLocationSet = false;
            while (playerLocationSet == false) { //keep trying until you get valid coords
                int x = randInt(1, 16);
                int y = randInt(1, 68);
                int playerX = getPlayer()->getPosition()->getXCoord();
                int playerY = getPlayer()->getPosition()->getYCoord();
                if (isMonsterAt(x, y) == true || isWallAt(x, y) == true) {
                    continue;
                } else {
                    m_player->getPosition()->setX(x-playerX);
                    m_player->getPosition()->setY(y-playerY);
                    playerLocationSet = true;
                }
            }
            
            clearScreen();
            display();
        }
        else { //player used another action/moves
            clearScreen();
            display();
        }
    }
}

void Game::display() { //add implementation for changing grid cells with items/objects/player/monster etc
    //m_gridUpdated starts off as objects that don't ever move (walls,stairs, golden idol)
    char m_gridUpdated[18][70] = {};
    for(int r = 0; r < 18; r++) {
        for(int c = 0; c < 70; c++) {
            m_gridUpdated[r][c] = m_grid[r][c];
        }
    }
    for (int i = 0; i < m_items.size(); i++) {
        int xCoord = m_items[i]->getPosition()->getXCoord();
        int yCoord = m_items[i]->getPosition()->getYCoord();
        char itemInitial = '\0'; //char for when something goes wrong
        string itemName = m_items[i]->getName();
        if (itemName == "mace" || itemName == "long sword" || itemName == "short sword" || itemName == "magic fangs of sleep" || itemName == "magic axe") {
            itemInitial = ')';
        }
        else if (itemName == "scroll of enhance dexterity" || itemName == "scroll of improve armor" || itemName == "scroll of raise strength" || itemName == "scroll of enhance health" || itemName == "scroll of teleportation") {
            itemInitial = '?';
        }
        m_gridUpdated[xCoord][yCoord] = itemInitial;
    }
    
    //monsters on the grid
    for (int i = 0; i < m_monsters.size(); i++) {
        string monsterName = m_monsters[i]->getName();
        char monsterInitial = ' ';
        if (monsterName == "Bogeyman") {
            monsterInitial = 'B';
        }
        else if (monsterName == "Snakewoman") {
            monsterInitial = 'S';
        }
        else if (monsterName == "Dragon") {
            monsterInitial = 'D';
        }
        else if (monsterName == "Goblin") {
            monsterInitial = 'G';
        }
        int monsterX = m_monsters[i]->getPosition()->getXCoord();
        int monsterY = m_monsters[i]->getPosition()->getYCoord();
        m_gridUpdated[monsterX][monsterY] = monsterInitial;
    }
    
    //player's position is @ on the grid (comes last)
    m_gridUpdated[m_player->getPosition()->getXCoord()][m_player->getPosition()->getYCoord()] = '@';
    
    //PRINT THE UPDATED GRID
    for(int r = 0; r < 18; r++){
        for(int c = 0; c < 70; c++){
            cout << m_gridUpdated[r][c];
        }
        cout << endl;
    }
    
    //PRINT STATS BAR
    cout << "Level: " << m_level << ", Hit points: " << getPlayer()->getHitPoints() << ", Armor: " << getPlayer()->getArmorPoints() << ", Strength: " << getPlayer()->getStrengthPoints() << ", Dexterity: " << getPlayer()->getDexterityPoints() << endl << endl; //1 line in between
    
    //PRINT MESSAGES WHILE RESETTING MESSAGES VECTOR
    for (int i = 0; i < m_messages.size(); i++) {
        cout << m_messages[i] << endl;
    }
    m_messages.clear();
}

void Game::createLevel() {
    //create the wall structure
    addWalls();
    //add stairway or golden idol depending on level
    addStairwayOrGoldenIdol();
    //add items (excluding stairway or golden idol)
    addItems();
    //add player (do it after items and stairway/idol to make sure player is on top if they are on same coord)
    addPlayer();
    //add monsters
    addMonster();
}

void Game::addWalls() {
    // Initialize the grid to walls
    for(int r = 0; r < 18; r++) {
        for(int c = 0; c < 70; c++) {
            m_grid[r][c] = '#';
        }
    }
    
    // Now add interior walls by defining rooms
    vector<Room> rooms;
    int numRooms = randInt(3, 5); // for example, starting with 4-5 rooms
    
    for (int i = 0; i < numRooms; i++) {
        Room room;
        int attempts = 0; // Counter to avoid infinite loop
        bool overlaps = true; // Initially assume overlap to enter the loop
        
        while (overlaps) {
            overlaps = false;
            room.width = randInt(8, 12); // rooms have a width between 3 and 8
            room.height = randInt(5, 8); // rooms have a height between 4 and 8
            room.x = randInt(1, 69 - room.width); // Ensure room fits within the grid bounds
            room.y = randInt(1, 17 - room.height);
            
            // Check for overlap with existing rooms
            for (int i = 0; i < rooms.size(); i++) {
                if (!(room.x + room.width < rooms[i].x + 1 || room.x > rooms[i].x + rooms[i].width + 1 ||
                      room.y + room.height < rooms[i].y + 1|| room.y > rooms[i].y + rooms[i].height + 1)) {
                    overlaps = true;
                    break;
                }
            }
            attempts++;
            if (attempts > 50) { // Break if too many attempts
                overlaps = false; // Exit loop if too many attempts without finding a spot
            }
        }
        
        if (attempts <= 50) {
            // Add the room to the list of rooms if a suitable spot was found
            rooms.push_back(room);
            
            // Fill in the room on the grid
            for (int r = room.y; r < room.y + room.height; ++r) {
                for (int c = room.x; c < room.x + room.width; ++c) {
                    m_grid[r][c] = ' ';
                }
            }
        }
    }
    
    // Connecting rooms with corridors
    for (int i = 0; i < rooms.size() - 1; i++) {
        Room current = rooms[i];
        Room next = rooms[i + 1];
        
        // Connect midpoints of rooms
        int midY_current = current.y + current.height / 2;
        int midX_current = current.x + current.width / 2;
        int midY_next = next.y + next.height / 2;
        int midX_next = next.x + next.width / 2;

        // Horizontal corridor
        for (int x = min(midX_current, midX_next); x <= max(midX_current, midX_next); x++) {
            m_grid[midY_current][x] = ' ';
        }

        // Vertical corridor
        for (int y = min(midY_current, midY_next); y <= max(midY_current, midY_next); y++) {
            m_grid[y][midX_next] = ' ';
        }
    }
}

void Game::addStairwayOrGoldenIdol() {
    if (m_level < 4) {
        bool stairwayAdded = false;
        while (stairwayAdded == false) {
            int x = randInt(1, 16); //1 - 68 bc 0 and 70 is guaranteed to be wall
            int y = randInt(1, 68);
            if (isItemAt(x, y) || isWallAt(x, y)) {
                continue;
            } else {
                m_grid[x][y] = '>';
                m_stairwayPosition = new Position(x,y);
                stairwayAdded = true;
            }
        }
    }
    else {
        bool idolAdded = false;
        while (idolAdded == false) {
            int x = randInt(1, 16);
            int y = randInt(1, 68);
            if (isItemAt(x, y) || isWallAt(x, y)) {
                continue;
            } else {
                m_grid[x][y] = '&';
                m_idolPosition = new Position(x,y);
                idolAdded = true;
            }
        }
    }
}

void Game::addItems() {
    int numberOfItems = randInt(2,3);
    for (int i = 0; i < numberOfItems; i++) {
        bool itemAdded = false;
        //while loop to keep trying random coords
        while (itemAdded == false) {
            int x = randInt(1, 16);
            int y = randInt(1, 68);
            if (isItemAt(x, y) == true || isWallAt(x, y) == true) {
                continue;
            }
            Position* position = new Position(x, y);
            int randomWeaponOrScroll = randInt(1,7);
            GameObject* newItem = nullptr;
            switch(randomWeaponOrScroll) { //random chance for each item
                case 1:
                    newItem = new Mace(position);
                    break;
                case 2:
                    newItem = new ShortSword(position);
                    break;
                case 3:
                    newItem = new LongSword(position);
                    break;
                case 4:
                    newItem = new ImproveArmor(position);
                    break;
                case 5:
                    newItem = new RaiseStrength(position);
                    break;
                case 6:
                    newItem = new EnhanceHealth(position);
                    break;
                case 7:
                    newItem = new EnhanceDexterity(position);
                    break;
            }
            if (newItem) {
                m_items.push_back(newItem); //add the item to the vector
                itemAdded = true;
            }
        }
    }
}

void Game::addPlayer() {
    bool playerAdded = false;
    while (playerAdded == false) {
        int x = randInt(1, 16);
        int y = randInt(1, 68);
        Position* position = new Position(x, y);
        if (isMonsterAt(x, y) == true || isWallAt(x, y) == true) {
            delete position;
            continue;
        } else {
            m_player = new Player(position);
            playerAdded = true;
        }
    }
}

void Game::addMonster() {
    int monsterCount = randInt(2,5*(m_level+1)+1);
    for (int i = 0; i < monsterCount; i++) {
        bool monsterAdded = false;
        while (monsterAdded == false) {
            int x = randInt(1, 16);
            int y = randInt(1, 68);
            if (isPlayerAt(x, y) == true || isWallAt(x, y) == true || isMonsterAt(x, y) == true) {
                continue;
            }
            Position* position = new Position(x, y); //create position of the future monster with valid coords
            Monster* newMonster = nullptr; //set newMonster to nullptr for now
            //create new monster but account for temple level
            if (m_level == 0 || m_level == 1) {
                int randomMonster = randInt(0,1);
                switch(randomMonster){
                    case 0:
                        newMonster = new Goblins(position); //bogeyman
                        break;
                    case 1:
                        newMonster = new Snakewomen(position); //snakewomen
                        break;
                }
            }
            else if (m_level == 2) {
                int randomMonster = randInt(0,2);
                switch(randomMonster){
                    case 0:
                        newMonster = new Bogeymen(position); //bogeyman
                        break;
                    case 1:
                        newMonster = new Snakewomen(position); //snakewomen
                        break;
                    case 2:
                        newMonster = new Goblins(position); //goblin
                        break;
                }
            }
            else if (m_level == 3 || m_level == 4) {
                int randomMonster = randInt(0,3);
                switch(randomMonster){
                    case 0:
                        newMonster = new Bogeymen(position); //bogeyman
                        break;
                    case 1:
                        newMonster = new Snakewomen(position); //snakewomen
                        break;
                    case 2:
                        newMonster = new Goblins(position); //goblin
                        break;
                    case 3:
                        newMonster = new Dragons(position); //dragon
                }
            }
            if (newMonster) { //if newMonster isn't null then add the monster
                m_monsters.push_back(newMonster);
                monsterAdded = true;
            }
        }
    }
}

bool Game::isWallAt(int r, int c) const {
    if (m_grid[r][c] == '#') {
        return true;
    }
    else {
        return false;
    }
}

bool Game::isPlayerAt(int r, int c) const {
    if (m_player == nullptr) {
        return false;
    }
    else if (m_player->getPosition()->getXCoord() != r && m_player->getPosition()->getYCoord() != c) {
        return false;
    }
    else {
        return true;
    }
}

bool Game::isMonsterAt(int r, int c) const {
    if (m_grid[r][c] == 'B' || m_grid[r][c] == 'S' || m_grid[r][c] == 'D' || m_grid[r][c] == 'G') {
        return true;
    } else {
        return false;
    }
}

bool Game::isItemAt(int r, int c) const {
    if (m_grid[r][c] == ')' || m_grid[r][c] == '?' || m_grid[r][c] == '>' || m_grid[r][c] == '&') {
        return true;
    } else {
        return false;
    }
}

char Game::getMapChar(Position* position) const { //return the char on that grid of the map
    if (isValidCoord(position)) {
        return m_grid[position->getXCoord()][position->getYCoord()];
    }
    else {
        return '\0';
    }
}

bool Game::isValidCoord(Position* position) const {
    if(position->getXCoord() >= 1 && position->getXCoord() <= 16 && position->getYCoord() >= 1 && position->getYCoord() <= 68) { //-1 for row and column bc walls are surrounding map
        return true;
    } else {
        return false;
    }
}

Player* Game::getPlayer() const {
    return m_player;
}

vector<Monster*>& Game::getMonsters() {
    return m_monsters;
}

vector<string>& Game::getMessages() {
    return m_messages;
}

vector<GameObject*>& Game::getItems() {
    return m_items;
}

Position* Game::getStairwayPosition() const {
    return m_stairwayPosition;
}

Position* Game::getIdolPosition() const {
    return m_idolPosition;
}

int Game::getGoblinSmellDistance() const {
    return m_goblinSmellDistance;
}
