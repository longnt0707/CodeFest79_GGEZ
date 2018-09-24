//
//  CElephant.h
//  GGEZcocoa
//
//  Created by Nguyen The Long on 9/12/18.
//  Copyright © 2018 Nguyen The Long. All rights reserved.
//

#ifndef CElephant_h
#define CElephant_h

#include <stdio.h>
#include <string>

#define POSITION_X_MIN 1
#define POSITION_X_MAX 29
#define POSITION_Y_MIN 1
#define POSITION_Y_MAX 29

class CElephant {
public:
    CElephant();
    ~CElephant();
    
    int64_t headPosX;
    int64_t headPosY;
    int64_t direction;
    int64_t prevX;
    int64_t prevY;
    int     atCorner; //0: running inside map, 1~4: one of the corner
    
    std::string nextMove();
    bool couldHitWall(int64_t move);
    bool validMoveForDirection(int64_t move);
};

#endif /* CElephant_hpp */
