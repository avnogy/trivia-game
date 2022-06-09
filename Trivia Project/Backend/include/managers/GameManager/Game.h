#pragma once
#include <vector>
#include <unordered_map>
#include "managers/GameManager/Question.h"
#include "managers/GameManager/GameData.h"
#include "managers/LoggedUser.h"
#include "responses/SubmitAnswerResponse.h"
#include "managers/GameManager/Question.h"

class Game
{
private:
	std::vector<Question> m_questions;
	std::unordered_map<LoggedUser, GameData> m_players;

public:
	Game(const std::vector<Question>& questions, const std::vector<std::string>& users);

	SubmitAnswerResponse submitAnswer(const LoggedUser& user, const std::string& answer);
	void removePlayer(const LoggedUser& user);
};

