#pragma once
#include "utils/utils.h"
#include "infrastructure/json/json.hpp"
struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	bool isActive;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(RoomData, id, name, maxPlayers, numOfQuestionsInGame, timePerQuestion, isActive);
};
