#pragma once
#include <string>
#include "json/json.hpp"
struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(RoomData,id,name,maxPlayers,numOfQuestionsInGame,timePerQuestion,isActive);
};
