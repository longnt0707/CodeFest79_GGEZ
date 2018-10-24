#pragma once

#include <string>
#include "../socketio_headers/sio_message.h"

#if _DEBUG || DEBUG
#ifdef _WINDOWS

#include <Windows.h>

static char MessageBuffer[1024];

#define DLOG(__x__) sprintf_s(MessageBuffer, 1024, "[debug]----" __x__); \
					OutputDebugStringA(MessageBuffer);

#else
#define DLOG(__x__) printf("\e[1;31m[debug]-----"); \
					printf(__x__); \
					printf("\e[0m\n");
#endif //_WINDOWS
#else
#define DLOG(__x__)
#endif //_DEBUG

// Server - match
enum API_CODE
{
	UN_KNOWN          = 0,
	SUCCESS           = 1,
	NOT_EXISTED_ROOM  = 100,
	INVALID_KEY       = 101,
	SYSTEM_ERROR      = 102,
	INVALID_PARAMETER = 103
};

enum ROUND_STATUS
{
	ROUND_NOT_STARTED = 0,
	ROUND_PLAYING     = 1,
	ROUND_PAUSE       = 2,
	ROUND_ENDED       = 3
};

// Map
struct CPoint {
	int64_t   x;
	int64_t   y;

	CPoint() {
		x = 1;
		y = 1;
	}

	CPoint(int64_t posX, int64_t posY) {
		x = posX;
		y = posY;
	}
};

struct CSize {
	int64_t   width;
	int64_t   height;

	CSize() {
		width = 1;
		height = 1;
	}

	CSize(int64_t x, int64_t y) {
		width  = x;
		height = y;
	}
};

const CPoint CORNER1 = CPoint(1 , 1);
const CPoint CORNER2 = CPoint(23, 1);
const CPoint CORNER3 = CPoint(1 , 23);
const CPoint CORNER4 = CPoint(23, 23);

// Player
enum DIRECTION
{
	MOVE_UP    = 1,
	MOVE_LEFT  = 2,
	MOVE_DOWN  = 3,
	MOVE_RIGHT = 4
};

//map return 24x24 -> 0 & 24 are wall; 1~23 are movable space
//max elephant = 23x23 = 529
#define MAX_ELEPHANTS_NUMBER 529
#define MAX_FOODS_NUMBER     50

struct Player {
	std::string id;
	std::string name;
	DIRECTION   direction;
	CPoint      segments[MAX_ELEPHANTS_NUMBER];
	int64_t     length; //added
	int64_t     score;
};

// Food
enum FOOD_TYPE
{
	FOOD_TYPE_NORMAL = 1,//red
	FOOD_TYPE_GOLDEN = 2,//yellow
	FOOD_TYPE_SUPER  = 3,//green
};

struct Food {
	std::string id;
	CPoint      coordinate;
	FOOD_TYPE   type;
};

// connection status
enum CONNECT_STATUS
{
	STATUS_NOTHING				= 0,
	STATUS_REQUEST_OK			= 1,
	STATUS_ROOM_INFO_OK			= 2,
	STATUS_ROUND_PLAYING		= 3,
	STATUS_ERROR_CODE			= 4,
	STATUS_ERROR_ROOM_INFO_NULL = 5,
	STATUS_ERROR_ROUND_NOT_PLAY = 6,
	STATUS_ERROR_OTHER          = 7,
};


class Message
{
public:
	API_CODE     code;
	std::string  status;
	ROUND_STATUS round_status;
	int64_t      round_time;
	CSize        map;
	int64_t      speed;
	Player       players[3];   // support 2 bots + 1 player
	int64_t      participants; // added
	int64_t      ourTeamIndex; // added 09-27
	Food         foods[MAX_FOODS_NUMBER];
	int64_t      foodstock;    // added

	Message();
	~Message();

	CONNECT_STATUS parsingIncomingRoomState(sio::message::ptr data);
};

/*
* Drive elephant
Data Format: JSON.

Data Structure:
- Requesting is executed successfully.
{
	"code": 1,
	"status": "OK"
}

- Requesting is executed failed.
{
	"code": xx,
	"status": "Error",
	"message": "xxxxxxxx"
}

Data Definition:
- code: The code of execution. Type of Number.
	1: Successful.
	100: The room have not created yet.
	101: Invalide key from client(mid or tid).
- status: The description of code. Type of String.
- message: The detail description of code. Type of String.
*/

/*
* Server incomming cycle
Data Format: JSON.

Data Structure:
- Requesting is executed successfully.
{
	"code": 1,
	"status": "OK",
	"round_status": xx,
	"round_time": xx,
	"map": { horizontal: xx, vertical: yy },
	"speed": xx,
	"players": [
		{
			"id": "xxxxx, name:"xxxxx",
			"direction": xx,
			"segments": [
				{"x: xxxx", "y": xxxx},
				{"x: xxxx", "y": xxxx},
				{"x: xxxx", "y": xxxx},
				{"x: xxxx", "y": xxxx}, ....
			],
			"score": xxxx
		},
		....
	],
	"foods": [
		{
			"id": "Food_xxxx",
			"coordinate": { "x": xxxx, "y": xxxx },
			"type: "NORMAL"
		},
		....
	]
}

- Requesting is executed failed.
{
	"code": xx,
	"status": "Error",
	"message": "xxxxxxxx"
}

Data Definition:
- code: The code of execution. Type of Number.
	1: Successful.
	100: The room have not created yet.
	101: Invalide key from client(mid or tid).
- round_status: The state of round. Type of Number.
	0: a round is not started.
	1: a round is playing.
	2: a round is pausing.
	3: a round is ended/closed.
- round_time: The remaining time of round in seconds.
- map: The information of map. Include size of map by horizotal and vertical squares.
- speed: The moving speed information of competitors on map.
- players: The array list of players(include you) on map.
	- direction: The current direction of elephant.
		The value of moving step is defined as below:
		1: Moving UP.
		2: Moving LEFT.
		3: Moving DOWN.
		4; Moving RIGHT.
	- segments: The array of positions of player's elephant members on map. The first item in array is position of Leader Elephant.
	- score: Current score of player on map.
- foods: The array list of foods(check point elephants) on map.
	- coordinate: The position of food on map.
	- type: The bonus point of food. There are 3 type of bonus point(NORMAL, SUPER, GOLDEN)
*/
