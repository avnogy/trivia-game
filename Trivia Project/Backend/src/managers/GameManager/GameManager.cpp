#include "managers/GameManager/GameManager.h"


/// <summary>
/// Creating a new game
/// </summary>
/// <param name="room"></param>
/// <returns></returns>
Game GameManager::createGame(const Room& room)
{
	Game game(IDatabase::instance()->getQuestions(), room.getAllUsers());
	m_games.push_back(game);
	return game;
}