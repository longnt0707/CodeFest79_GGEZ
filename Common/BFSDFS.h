

#ifndef BFSDFS_h
#define BFSDFS_h

#include <stdio.h>
#include <string>
#include "Message.h"


class BFSDFS {
public:
	BFSDFS();
    ~BFSDFS();
   
	// call once
	void initMatrix(int64_t n, int64_t m);
	
	// call each cycle
	void updatePlayerMatrix(Message msgData);
	void setStartXY(int64_t x, int64_t y);
	void updateFoodMatrix(Food foods[], int64_t stock);

	// get move each cycle
	std::string nextMove();
};

#endif /* BFSDFS_h */
