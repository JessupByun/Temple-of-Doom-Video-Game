//
//  GameObject.cpp
//  cs32project3
//
//  Created by Jessup Byun on 5/11/24.
//

#include "GameObject.h"
#include <string>
using namespace std;

//constructor and destructor
GameObject::GameObject(string name, Position* position) : m_name(name), m_position(position) {}

GameObject::~GameObject() {}

//getter functions

string GameObject::getName()
{
    return m_name;
}

Position* GameObject::getPosition() const {
    return m_position;
}
