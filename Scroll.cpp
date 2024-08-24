//
//  Scroll.cpp
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include "Scroll.h"
using namespace std;

//constructor and destructor
Scroll::Scroll(string name, Position* position) : GameObject(name, position) {}

Scroll::~Scroll() {}

int Scroll::getBonusDexterity() const {
    return 0;
}

int Scroll::getDamageAmount() const {
    return 0;
}
