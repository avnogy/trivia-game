#include "managers/GameManager/GameManager.h"
#include "infrastructure/database/UpdateQuestions.h"
/// <summary>
/// Creating a new game
/// </summary>
/// <param name="room"></param>
/// <returns></returns>
Game* GameManager::createGame(const Room& room)
{
	if (updateQuestions())
	{
		std::cout << "populated questions." << std::endl;
	}
	else
	{
		std::cout << "error while adding questions." << std::endl;
	}

	Game* game = new Game(IDatabase::instance()->getQuestions(), room.getAllUsers());
	m_games.push_back(game);
	return game;
};