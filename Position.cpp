//
//  Position.cpp
//  cs32project3
//
//  Created by Jessup Byun on 5/12/24.
//

#include "Position.h"

Position::Position(int x, int y) : m_x(x), m_y(y) {}

void Position::setX(int xChange) { //adds xChange to m_x
    m_x = m_x + xChange;
}

void Position::setY(int yChange) { //adds yChange to m_y
    m_y = m_y + yChange;
}

int Position::getXCoord() {
    return m_x;
}

int Position::getYCoord() {
    return m_y;
}

