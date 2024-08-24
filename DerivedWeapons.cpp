//
//  DerivedWeapons.cpp
//  cs32project3
//
//  Created by Jessup Byun on 5/12/24.
//

#include "DerivedWeapons.h"
using namespace std;

//Mace implementations
Mace::Mace(Position* position) : Weapon("mace", position, 2, 0) {}

Mace::~Mace() {}

string Mace::actionDescription() const {
    return "swings mace at ";
}

void Mace::ability(Game& game) {}

//ShortSword implementations

ShortSword::ShortSword(Position* position) : Weapon("short sword", position, 2, 0) {}

ShortSword::~ShortSword() {}

string ShortSword::actionDescription() const {
    return "slashes short sword at ";
}

void ShortSword::ability(Game& game) {}

//LongSword implementations

LongSword::LongSword(Position* position) : Weapon("long sword", position, 4, 2) {}

LongSword::~LongSword() {}

string LongSword::actionDescription() const {
    return "swings long sword at ";
}

void LongSword::ability(Game& game) {}

//MagicAxe implementations

MagicAxe::MagicAxe(Position* position) : Weapon("magic axe", position, 5, 5) {}

MagicAxe::~MagicAxe() {}

string MagicAxe::actionDescription() const {
    return "chops magic axe at ";
}

void MagicAxe::ability(Game& game) {}

//MagicFang implementations

MagicFang::MagicFang(Position* position) : Weapon("magic fangs of sleep", position, 2, 3) {}

MagicFang::~MagicFang() {}

string MagicFang::actionDescription() const {
    return "strikes magic fangs at ";
}

void MagicFang::ability(Game& game) {} //magic fangs of sleep does have an ability, but it is implemented in actor's special magic fang sleep function

