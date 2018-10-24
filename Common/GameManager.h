
#pragma once

#include <string>
#include "Message.h"

// Socket IO events
#define PLAYER_OUTGOING_JOIN_ROOM             "player join room"
#define PLAYER_OUTGOING_DRIVE_ELEPHANT        "player drive elephant"
#define PLAYER_INCOMMING_ROOM_STATE           "player room state"
#define PLAYER_INCOMMING_DRIVE_ELEPHANT_STATE "player drive elephant state"

// Addresses & IDs
#define UNIQUE_TEAM_NAME				"GGEZ_:V"
#define UNIQUE_TEAM_ID					"5b76dd170273602fd9d05e84"
#define UNIQUE_TEAM_ID_INPLAY			"5b76dd170273602fd9d05e85"
//#define UNIQUE_TEAM_ID_INPLAY_100CAN    "5b76dc430273602fd9d05e73"

#define UNIQUE_SERVER_ADDRESS_FIRST     "http://codefest79.satek.vn/"
#define UNIQUE_SERVER_PUBLIC_IP         "http://54.255.181.99/"
#define UNIQUE_SERVER_ADDRESS_SECOND    "http://codefest79.techover.io/"
#define UNIQUE_SERVER_LOCAL_IP_TEST     "http://192.168.0.105/"
#define UNIQUE_SERVER_LOCAL_IP_MATCH1   "http://192.168.0.103/"       //match1 0925
#define UNIQUE_SERVER_LOCAL_IP_MATCH2   "http://192.168.0.100/"       //match2 0928
#define UNIQUE_SERVER_LOCAL_IP_MATCH3   "http://192.168.0.100/"       //match3 1004
#define UNIQUE_SERVER_LOCAL_IP_MATCH4   UNIQUE_SERVER_LOCAL_IP_MATCH3 //match4 1004

#define UNIQUE_MATCH_ID_TRAINING_FIRST       "5b76dd170273602fd9d05e84"
#define UNIQUE_MATCH_ID_TRAINING_GGEZ        "5ba86d9ff8e4b56196601eeb"
#define UNIQUE_MATCH_ID_TRAINING_100CAN      "5ba247c6837605227461ccfa"
#define UNIQUE_MATCH_ID_TRAINING_GGEZ_LOCAL  "5badc2a5c62f675a7316d449"
#define UNIQUE_MATCH_ID_BE_V1_259_3     "5b991707be34b16194b8191c" //match1 0925 vs Cam Quit 1-0-0
#define UNIQUE_MATCH_ID_BE_V2_279_2     "5ba1b47407330e1b8112e995" //match2 0928 vs Iron Man 0-1-1

#define UNIQUE_MATCH_ID_BE_V5_410_3     "5ba36e97baa3420274998719" //match3 1004 vs Bravo
#define UNIQUE_MATCH_ID_BE_V4_410_12    "5ba367b4baa3420274998710" //match4 1004 vs Tien Nu

// Update here for each match
#define UNIQUE_SERVER_ADDRESS_CURRENT    UNIQUE_SERVER_LOCAL_IP_MATCH4
#define UNIQUE_MATCH_ID_CURRENT          UNIQUE_MATCH_ID_BE_V4_410_12

/*
	Wifi FSoft Guest
	Account: CodeFest79
	Password: FPTSOFTWARE

    Guest-0184229
    guest-0184229
*/

class GameManager
{
private:
	std::string serverAddress;
	std::string tID;
	std::string mID;
	std::string tName;
	std::string tIDPlaying;

public:
	static GameManager& Shared()
	{
		static GameManager instance;
		return instance;
	}

	GameManager();
	~GameManager();

	void SocketIOStartConnect(std::string server);
	void SocketIOJoinRoom(std::string matchID);
    void SocketIOQuit();

	void SendElephants(std::string moves);
};


/*
 * Map 23x23, 10 food: average cost for 1 food: 7.0 (1.0 ~ 1 movement)
 * Cost of Death: 10 food + 10 seconds = 10*7.0 + 10*5 (speed 5: 5 movement/second) = 120.0
 */




