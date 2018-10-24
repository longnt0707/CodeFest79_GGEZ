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

    prevX = 1;
    prevY = 1;
}

CElephant::~CElephant() {
    ;
}

std::string CElephant::nextMoveRandom()
{
	//Windows random generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 4);
    
		int move = dist(gen);
        
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
    
    return "4";
}










