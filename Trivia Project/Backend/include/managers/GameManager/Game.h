#pragma once
#include <vector>
#include <unordered_map>
#include "managers/GameManager/Question.h"
#include "managers/GameManager/GameData.h"
#include "managers/LoggedUser.h"
#include "responses/SubmitAnswerResponse.h"
#include "managers/GameManager/Question.h"
#include "responses/GetGameResultsResponse.h"

class Game
{
private:
	std::vector<Question> m_questions;
	std::unordered_map<LoggedUser, GameData> m_players;

public:
	Game(const std::vector<Question>& questions, const std::vector<std::string>& users);

	std::vector<PlayerResults> getGameResults() const;
	std::vector<Question> getQuestions() const;
	Question getQuestionForUser(const LoggedUser& user) const;
	void submitAnswer(const LoggedUser& user, const std::string& answer) ;
	void removePlayer(const LoggedUser& user);
};

