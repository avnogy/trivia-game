#pragma once
#include <queue>
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
	std::queue<Question> m_questions;
	std::unordered_map<LoggedUser, GameData> m_players;
	Question& m_currentQuestion;

public:
	Game(const std::queue<Question>& questions, const std::vector<std::string>& users);

	std::vector<PlayerResults> getGameResults() const;
	std::queue<Question> getQuestions() const;
	const Question& getQuestion();
	void submitAnswer(const LoggedUser& user, const std::string& answer) ;
	void removePlayer(const LoggedUser& user);
};

