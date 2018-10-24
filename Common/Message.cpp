#include "Message.h"

Message::Message()
{
	code = UN_KNOWN;
	status = std::string("");
	round_status = ROUND_NOT_STARTED;
	round_time = 180; // 3 * 60
	map = CSize(23, 23);
	speed = 0;

	for (size_t i = 0; i < 3; i++)
	{
		players[i].id = std::string("");
		players[i].name = std::string("");
		players[i].direction = MOVE_RIGHT;
		memset(players[i].segments, 0, MAX_ELEPHANTS_NUMBER * sizeof(CPoint));
		players[i].length = 1; // head only
		players[i].score = 0;
	}

	ourTeamIndex = 0;

	for (size_t i = 0; i < MAX_FOODS_NUMBER; i++)
	{
		foods[i].id = std::string("");
		foods[i].coordinate = CPoint(1, 1);
		foods[i].type = FOOD_TYPE_NORMAL;
	}
}


Message::~Message()
{
}

// Parsing all
CONNECT_STATUS Message::parsingIncomingRoomState(sio::message::ptr data)
{
	code = (API_CODE)data->get_map()["code"]->get_int();
	status = data->get_map()["status"]->get_string();

	if (code != SUCCESS)
	{
		return STATUS_ERROR_CODE;
	}

	sio::message::ptr roomInfo = data->get_map()["roomInfo"];
	if (!roomInfo)
	{
		return STATUS_ERROR_ROOM_INFO_NULL;
	}

	sio::message::ptr mapData = roomInfo->get_map()["map"];
	map.width = mapData->get_map()["horizontal"]->get_int();
	map.height = mapData->get_map()["vertical"]->get_int();

	round_status = (ROUND_STATUS)roomInfo->get_map()["round_status"]->get_int();

	// 0927 comment out: send move even when not playing
	/*if (round_status != ROUND_PLAYING)
	{
		return STATUS_ERROR_ROUND_NOT_PLAY;
	}*/

	//Round info
	//TODO: round_time, speed

	// Round is in PLaying
	// array_message for players
	std::vector<std::shared_ptr<sio::message>> playersData = roomInfo->get_map()["players"]->get_vector();
    participants = playersData.size();// capacity();
	if (participants > 3)
	{
		return STATUS_ERROR_OTHER; // not supported
	}

	for (int i = 0; i < participants; i++) {
		sio::message::ptr playerI = playersData.at(i);

		players[i].name = playerI->get_map()["name"]->get_string();
        players[i].id = playerI->get_map()["id"]->get_string();
		players[i].score = playerI->get_map()["score"]->get_int();
		players[i].direction = (DIRECTION)playerI->get_map()["direction"]->get_int();

		// array_message
		std::vector<std::shared_ptr<sio::message>> segments = playerI->get_map()["segments"]->get_vector();
        players[i].length = segments.size(); //capacity();

		// get all elephants of player
		for (int j = 0; j < players[i].length; j++) {
			sio::message::ptr segment = segments.at(j);

			players[i].segments[j].x = segment->get_map()["x"]->get_int();
			players[i].segments[j].y = segment->get_map()["y"]->get_int();
		}
	}

	// array_message for food
	std::vector<std::shared_ptr<sio::message>> foodsData = roomInfo->get_map()["foods"]->get_vector();
    foodstock = foodsData.size(); //capacity();
	for (int64_t i = 0; i < foodstock; i++)
	{
		sio::message::ptr food = foodsData.at(i);

		//TODO: id, color

		sio::message::ptr coordinate = food->get_map()["coordinate"];
		foods[i].coordinate.x = coordinate->get_map()["x"]->get_int();
		foods[i].coordinate.y = coordinate->get_map()["y"]->get_int();

		std::string type = food->get_map()["type"]->get_string();
		if (type.compare("NORMAL") == 0)
		{
			foods[i].type = FOOD_TYPE_NORMAL;
		}
		else if (type.compare("GOLDEN") == 0)
		{
			foods[i].type = FOOD_TYPE_GOLDEN;
		}
		else if (type.compare("SUPER") == 0)
		{
			foods[i].type = FOOD_TYPE_SUPER;
		}
	}

	return STATUS_ROUND_PLAYING;
}
