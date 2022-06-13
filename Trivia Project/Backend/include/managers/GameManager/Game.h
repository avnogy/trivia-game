#pragma once
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "infrastructure/Communicator.h"
#include "managers/GameManager/Question.h"
#include "managers/GameManager/GameData.h"
#include "managers/LoggedUser.h"
#include "responses/SubmitAnswerResponse.h"
#include "managers/GameManager/Question.h"
#include "responses/GetGameResultsResponse.h"

#include <thread>
#include <mutex>

class Game
{
private:
	std::queue<Question> m_questions;
	Question m_currentQuestion;
	std::unordered_map<LoggedUser, GameData> m_players;

	std::unordered_set<std::string> m_submitCount;
	std::mutex m_submitCountMutex;
	std::thread m_sendCorrectAnswers;

public:
	Game(const std::queue<Question>& questions, const std::vector<std::string>& users);

	bool isAllSubmited();

	std::queue<Question> getQuestions() const;
	const Question&		 getQuestion() const;
	void				 nextQuestion();
	std::vector<PlayerResults> getGameResults() const;

	void submitAnswer(const LoggedUser& user, const std::string& answer) ;
	void removePlayer(const LoggedUser& user);

	static void sendCorrectAnswers(Game* game);
};

