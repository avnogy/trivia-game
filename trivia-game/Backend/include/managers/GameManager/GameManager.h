#pragma once
#include "managers/GameManager/Game.h"
#include "managers/RoomManager/Room.h"
#include "infrastructure/database/IDatabase.h"

class Game;

class GameManager
{
	MAKE_SINGLETON(GameManager);
	DELETE_CONSTRUCTOR(GameManager);

private:
	std::vector<Game*> m_games;

public:
	Game* createGame(const Room& room);
};
