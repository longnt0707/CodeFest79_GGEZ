#include "GameManager.h"
#include "SocketIOManager.h"
#include "CElephant.h"

#ifdef _DEBUG
#define DLOG(__x__) printf("\e[1;31m[debug]-----");\
                    printf __x__;\
                    printf("\e[0m\n");
#else
#define DLOG(__x__)
#endif

void OnIncommingRoomState(sio::event& event);

GameManager::GameManager()
{
	serverAddress = std::string(UNIQUE_SERVER_ADDRESS);
	tID = std::string(UNIQUE_TEAM_ID);
	mID = std::string(UNIQUE_MATCH_ID_TRAINING);
	tName = std::string(UNIQUE_TEAM_NAME);
}


GameManager::~GameManager()
{
}

void GameManager::SocketIOStartConnect(std::string server)
{
	socketioStartConnect(server);

	socketioRegisterEvent(PLAYER_INCOMMING_ROOM_STATE, OnIncommingRoomState);
}

void GameManager::SocketIOJoinRoom(std::string matchID)
{
    socketioJoinRoom(UNIQUE_TEAM_ID, matchID, PLAYER_OUTGOING_JOIN_ROOM);
}

void GameManager::SendElephants(std::string moves)
{
	socketioSendElephentArmy(tID, mID, moves, PLAYER_OUTGOING_DRIVE_ELEPHANT);
}


// Event handler
static int moveCount = 0;
//
void OnIncommingRoomState(sio::event& event) {
	sio::message::ptr data = event.get_message();
	int64_t code = data->get_map()["code"]->get_int();
	std::string status = data->get_map()["status"]->get_string();

	DLOG(("Room_State code: %lld", code));

	if (code == 1) {
		sio::message::ptr roomInfo = data->get_map()["roomInfo"];
		if (roomInfo) {
			int64_t round_status = roomInfo->get_map()["round_status"]->get_int();
			if (round_status == 1) {

				// array_message
				std::vector<std::shared_ptr<sio::message>> players = roomInfo->get_map()["players"]->get_vector();

				CElephant MyElephant = CElephant();

				int64_t participants = players.capacity();
				for (int i = 0; i < participants; i++) {
					sio::message::ptr playerI = players.at(i);

					std::string name = playerI->get_map()["name"]->get_string();
					std::string trueName = std::string(UNIQUE_TEAM_NAME);

					if (name.compare(trueName) == 0) {
						int64_t direction = playerI->get_map()["direction"]->get_int();
						MyElephant.direction = direction;

						// array_message
						std::vector<std::shared_ptr<sio::message>> segments = playerI->get_map()["segments"]->get_vector();
						int64_t length = segments.capacity();
						for (int j = 0; j < length; j++) {
							sio::message::ptr head = segments.at(j);

							MyElephant.prevX = MyElephant.headPosX;
							MyElephant.prevY = MyElephant.headPosY;
							MyElephant.headPosX = head->get_map()["x"]->get_int();
							MyElephant.headPosY = head->get_map()["y"]->get_int();

							if (moveCount != 0 && MyElephant.prevX == MyElephant.headPosX && MyElephant.prevY == MyElephant.headPosY) {
								// elephent is idle or being penaltied)
								moveCount = 0;
							}
							break;
						}
						break;
					}
				}

				if (moveCount == 0) {
					if (MyElephant.headPosX == POSITION_X_MIN) {
						if (MyElephant.headPosY == POSITION_Y_MIN) {
							MyElephant.atCorner = 1;
						}
						else if (MyElephant.headPosY == POSITION_Y_MAX) {
							MyElephant.atCorner = 2;
						}
					}
					else if (MyElephant.headPosX == POSITION_X_MAX) {
						if (MyElephant.headPosY == POSITION_Y_MIN) {
							MyElephant.atCorner = 4;
						}
						else if (MyElephant.headPosY == POSITION_Y_MAX) {
							MyElephant.atCorner = 3;
						}
					}
				}
				std::string moves = MyElephant.nextMove();
				GameManager::Shared().SendElephants(moves);
				moveCount++;
			}
		}
	}

	return;
}
