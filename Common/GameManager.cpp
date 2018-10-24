#include "GameManager.h"
#include "SocketIOManager.h"
#include "CElephant.h"
#include "BFSDFS.h"

void OnIncommingRoomState(sio::event& event);

static Message DefaultMessage = Message();

GameManager::GameManager()
{
    serverAddress = std::string(UNIQUE_SERVER_ADDRESS_CURRENT);
	mID           = std::string(UNIQUE_MATCH_ID_CURRENT);
    
    tID           = std::string(UNIQUE_TEAM_ID);
	tName         = std::string(UNIQUE_TEAM_NAME);
	tIDPlaying    = std::string(UNIQUE_TEAM_ID_INPLAY);
}


GameManager::~GameManager()
{
}

void GameManager::SocketIOStartConnect(std::string server)
{
    serverAddress = server;
    
	socketioStartConnect(server);
	socketioRegisterEvent(PLAYER_INCOMMING_ROOM_STATE, OnIncommingRoomState);
}

void GameManager::SocketIOJoinRoom(std::string matchID)
{
    mID = matchID;
	socketioJoinRoom(UNIQUE_TEAM_ID, matchID, PLAYER_OUTGOING_JOIN_ROOM);
}

void GameManager::SocketIOQuit()
{
    socketioClose();
}

void GameManager::SendElephants(std::string moves)
{
	socketioSendElephentArmy(tID, mID, moves, PLAYER_OUTGOING_DRIVE_ELEPHANT);
}


// Event handler
static int cycleCount = 0;
static CElephant MyElephant;
static BFSDFS bfsdfs;
//

#define USING_TEAM_ID
#define USING_BFSDFS
#include <chrono>

void OnIncommingRoomState(sio::event& event) {
	sio::message::ptr data = event.get_message();

	auto check0 = std::chrono::high_resolution_clock::now();
	CONNECT_STATUS stat = DefaultMessage.parsingIncomingRoomState(data);

	if (DefaultMessage.code == API_CODE::SUCCESS) {
		
		if (stat != CONNECT_STATUS::STATUS_ERROR_ROOM_INFO_NULL) {

			if (cycleCount == 0)
			{
				cycleCount++;
			}

			// 0927 comment out: send move even when not playing
//            if (DefaultMessage.round_status == ROUND_STATUS::ROUND_PLAYING) {
#ifdef USING_TEAM_ID
            std::string teamId = std::string(UNIQUE_TEAM_ID_INPLAY);
            for (int64_t i = 0; i < DefaultMessage.participants; i++)
            {
                if (DefaultMessage.players[i].id.compare(teamId) == 0)
                {
                    DefaultMessage.ourTeamIndex = i;
                    break;
                }
            }
#else
            std::string teamName = std::string(UNIQUE_TEAM_NAME);
            for (int64_t i = 0; i < DefaultMessage.participants; i++)
            {
                if (DefaultMessage.players[i].name.compare(teamName) == 0)
                {
                    DefaultMessage.ourTeamIndex = i;
                    break;
                }
            }
#endif
            
#ifdef USING_BFSDFS
            bfsdfs.initMatrix(DefaultMessage.map.width - 1, DefaultMessage.map.height - 1);
            // update player position
            bfsdfs.updatePlayerMatrix(DefaultMessage);

            // update head position
            bfsdfs.setStartXY(DefaultMessage.players[DefaultMessage.ourTeamIndex].segments[0].x,
                              DefaultMessage.players[DefaultMessage.ourTeamIndex].segments[0].y);

            // update foods
            bfsdfs.updateFoodMatrix(DefaultMessage.foods, DefaultMessage.foodstock);

            auto check1 = std::chrono::high_resolution_clock::now();
            std::string move = bfsdfs.nextMove();
            auto check2 = std::chrono::high_resolution_clock::now();
#endif
            GameManager::Shared().SendElephants(move);
            auto check3 = std::chrono::high_resolution_clock::now();
            
            std::chrono::duration<double, std::milli> elapsed2 = check2 - check1;
            std::chrono::duration<double, std::milli> elapsed3 = check3 - check2;
            std::chrono::duration<double, std::milli> oneCycle = check3 - check0;
            static double sum = 0.0;
            static int count = 0;
            static double max = 0.0;
            if (DefaultMessage.round_status == ROUND_STATUS::ROUND_PLAYING) {
                sum += oneCycle.count();
                count++;
                if (max < oneCycle.count()) {
                    max = oneCycle.count();
                }
            }
            
            printf("[debug]---- move No. %d, average %f ms, max %f, time[%f %f |%f], moves %s, score %lld\n\n",
                   count, sum/count, max,
                   elapsed2.count(), elapsed3.count(), oneCycle.count(),
                   move.c_str(), DefaultMessage.players[DefaultMessage.ourTeamIndex].score);
#if _WINDOWS && _DEBUG
            sprintf_s(MessageBuffer, 1024,
                      "[debug]---- move No. %d, average %f ms, max %f, time[%f %f |%f], moves %s, score %lld\n\n",
                      count, sum/count, max,
                      elapsed2.count(), elapsed3.count(), oneCycle.count(),
                      move.c_str(), DefaultMessage.players[DefaultMessage.ourTeamIndex].score);
            OutputDebugStringA(MessageBuffer);
#endif //_WINDOWS
//            } //ROUND_STATUS::ROUND_PLAYING
		}
	}

	return;
}
