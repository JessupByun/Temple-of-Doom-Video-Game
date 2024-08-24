//
//  Game.h
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

class Player;
class Monster;
class Weapon;
class GameObject;
class Position;

#include <string>
#include <vector>

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.

class Game
{
public:
    //constructor and destructor
    Game(int goblinSmellDistance);
    ~Game();
    
    void play();
    void createLevel();
    void display();
    char getMapChar(Position* position) const;
    bool isValidCoord(Position* position) const;
    
    //functions to check location
    bool isPlayerAt(int r, int c) const;
    bool isMonsterAt(int r, int c) const;
    bool isWallAt(int r, int c) const;
    bool isItemAt(int r, int c) const;
    
    //getters
    Player* getPlayer() const;
    std::vector<Monster*>& getMonsters();
    std::vector<std::string>& getMessages();
    std::vector<GameObject*>& getItems();
    Position* getStairwayPosition() const;
    Position* getIdolPosition() const;
    int getGoblinSmellDistance() const;

private:
    char m_grid[18][70];
    int m_level;
    Player* m_player;
    Position* m_stairwayPosition;
    Position* m_idolPosition;
    std::vector<Monster*> m_monsters;
    std::vector<GameObject*> m_items;
    std::vector<std::string> m_messages;
    int m_goblinSmellDistance;
    
    //helper functions for display
    void addPlayer();
    void addMonster();
    void addWalls();
    void addItems();
    void addStairwayOrGoldenIdol();
};

#endif // GAME_INCLUDED
