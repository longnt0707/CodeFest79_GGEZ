//
//  CElephant.cpp
//  GGEZcocoa
//
//  Created by Nguyen The Long on 9/12/18.
//  Copyright © 2018 Nguyen The Long. All rights reserved.
//

#include <random>
#include "CElephant.h"

CElephant::CElephant() {
    direction = 4;
    headPosX = 1;
    headPosY = 1;
    prevX = 1;
    prevY = 1;
}

CElephant::~CElephant() {
    ;
}

std::string CElephant::nextMove()
{
	//Windows random generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 4);

    bool valid = false;
    int safeCount = 0;
    
    while (!valid) {
		int move = dist(gen);
        
        safeCount++;
        if (safeCount == 10) {
            valid = true;
        }
        
        if (atCorner == 0 && !validMoveForDirection(move)) {
            continue;
        }
        if (couldHitWall(move)) {
            continue;
        }
        
        switch (move) {
            case 1:
                return "1";
                break;
            case 2:
                return "2";
                break;
            case 3:
                return "3";
                break;
            case 4:
                return "4";
                break;
            default:
                return "4";
                break;
        }
    }
    
    return "4";
}

bool CElephant::couldHitWall(int64_t move)
{
    if (headPosX == POSITION_X_MIN && move == 2) {
        return true;
    }
    else if (headPosX == POSITION_X_MAX && move == 4) {
        return true;
    }
    else if (headPosY == POSITION_Y_MIN && move == 1) {
        return true;
    }
    else if (headPosY == POSITION_Y_MAX && move == 3) {
        return true;
    }
    else {
        return false;
    }
}

bool CElephant::validMoveForDirection(int64_t move)
{
    int64_t check = move + direction;
    if (check == 4 || check == 6) {
        //reverse move
        return false;
    } else {
        return true;
    }
}









