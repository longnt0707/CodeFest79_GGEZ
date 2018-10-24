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
#include "Message.h"

#define MAP_X_MAX 50
#define MAP_Y_MAX 50

class CElephant {
    Message GameState;
    int Map[MAP_X_MAX][MAP_Y_MAX];
    
public:
    CElephant();
    ~CElephant();
    
    int64_t headPosX;
    int64_t headPosY;
    int64_t direction;
    int64_t prevX;
    int64_t prevY;
    int     atCorner; //0: running inside map, 1~4: one of the corner

	Food    foods[100];
	int64_t foodCount;

	int64_t map_width;
	int64_t map_height;

	CPoint  player0[MAX_ELEPHANTS_NUMBER];
	CPoint  player1[MAX_ELEPHANTS_NUMBER]; //Opponent
	int64_t player0_length; //include head
	int64_t player1_length;

    std::string nextMoveRandom();
};

/*
direction
    1
2       4
    3
corner
1       4
2       3
*/

#endif /* CElephant_h */
