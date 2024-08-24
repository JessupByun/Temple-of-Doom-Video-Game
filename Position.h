//
//  Position.h
//  cs32project3
//
//  Created by Jessup Byun on 5/12/24.
//

#ifndef Position_h
#define Position_h

struct Position {
    int m_x;
    int m_y;
    Position (int x = 0, int y = 0);
    
    //setters
    void setX(int xChange);
    void setY(int yChange);
    
    //getters
    int getXCoord();
    int getYCoord();
};

#endif /* Position_h */
