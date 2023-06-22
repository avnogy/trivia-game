#include "infrastructure/database/SqliteDataBase.h"

/// <summary>
/// creates a database instence
/// </summary>
/// <param name="databasePath"> </param>
/// <returns></returns>
SqliteDataBase::SqliteDataBase(const std::string& databasePath) :
	m_filePath(databasePath)
{
	//checking if can access file
	int doesFileExist = _access(m_filePath.c_str(), 0);

	//attempting database open
	int res = sqlite3_open(m_filePath.c_str(), &m_db);

	if (res != SQLITE_OK)
	{
		m_db = nullptr;
		throw DatabaseError("Failed to open Sqlite database.");
	}
	if (doesFileExist == -1)
	{
		//users table
		sqlexec(R"(
				CREATE TABLE users(
				user_id		INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
				name		TEXT NOT NULL,
				password	TEXT NOT NULL,
				email		TEXT NOT NULL);
			)");

		//statistics table
		sqlexec(R"(
				CREATE TABLE statistics(
				statistics_id		INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
				user_id				INTEGER NOT NULL,
				averageAnswerTime	FLOAT	NOT NULL,
				numOfCorrectAnswers INTEGER NOT NULL,
				numOfTotalAnswers	INTEGER NOT NULL,
				numOfPlayerGames	INTEGER NOT NULL,
				FOREIGN KEY (user_id) REFERENCES users(user_id));
			)");

		//questions table
		sqlexec(R"(
				CREATE TABLE questions(
				question_id			INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
				question			TEXT NOT NULL,
				correctAnswer		TEXT NOT NULL,
				possibleAnswer1		TEXT NOT NULL,
				possibleAnswer2		TEXT NOT NULL,
				possibleAnswer3		TEXT NOT NULL);
			)");
	}
}

/// <summary>
/// destructs the database instence
/// </summary>
SqliteDataBase::~SqliteDataBase()
{
	//closing database
	sqlite3_close(m_db);
	m_db = nullptr;
}

/// <summary>
/// Excecute a query to database
/// </summary>
/// <param name="msg">query</param>
/// <param name="callback">callback function to query</param>
/// <param name="callbackArg">argument to callback</param>
/// <returns>whether the query succeeded</returns>
bool SqliteDataBase::sqlexec(const std::string& msg, int(*callback)(void* data, int argc, char** argv, char** azColName), void* callbackArg) const
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(m_db, msg.c_str(), callback, callbackArg, &errMessage);

	return (res == SQLITE_OK);
}

/// <summary>
/// checks if given user exists in the database
/// </summary>
/// <param name="username"></param>
/// <returns></returns>
bool SqliteDataBase::doesUserExist(const std::string& username) const
{
	//preparing a statement so it can be checked
	struct sqlite3_stmt* selectstmt;
	int result = sqlite3_prepare_v2(m_db, ("SELECT * FROM users WHERE name = \"" + username + "\";").c_str(), -1, &selectstmt, NULL);
	if (result == SQLITE_OK)
	{
		//if row was returned the user exists
		bool found = sqlite3_step(selectstmt) == SQLITE_ROW;
		sqlite3_finalize(selectstmt);
		return found;
	}
	else
	{
		throw SQLITE_DATABASE_ERROR;
	}
}

/// <summary>
/// checks if given password matches the user
/// </summary>
/// <param name="username"></param>
/// <param name="password"></param>
/// <returns></returns>
bool SqliteDataBase::doesPasswordMatch(const std::string& username, const std::string& password) const
{
	//preparing a statement so it can be checked
	struct sqlite3_stmt* selectstmt;
	int result = sqlite3_prepare_v2(m_db, ("SELECT * FROM users WHERE name = \"" + username + "\" AND password = \"" + password + "\"; ").c_str(), -1, &selectstmt, NULL);
	if (result == SQLITE_OK)
	{
		//if row was returned the password matches the user
		bool match = sqlite3_step(selectstmt) == SQLITE_ROW;
		sqlite3_finalize(selectstmt);
		return match;
	}
	else
	{
		throw SQLITE_DATABASE_ERROR;
	}
}

/// <summary>
/// adds a new user to the database
/// </summary>
/// <param name="username"></param>
/// <param name="password"></param>
/// <param name="email"></param>
void SqliteDataBase::addNewUser(const std::string& username, const std::string& password, const std::string& email) const
{
	if (!sqlexec("INSERT INTO users (name,password,email) VALUES (\"" + username + "\",\"" + password + "\",\"" + email + "\");"))
	{
		throw DatabaseError("Sql request failed, Couldn't add user");
	}
}

/// <summary>
/// getting from the database the average answer time of a player
/// </summary>
/// <param name="username">player username</param>
/// <returns>average answer time</returns>
float SqliteDataBase::getPlayerAverageAnswerTime(const std::string& username) const
{
	float averageAnswerTime = 0;

	//callback function will assign query result to averageAnswerTime
	auto callback = [](void* data, int argc, char** argv, char** azColName) -> int
	{
		if (argc == 0)
		{
			*(float*)data = 0;
			return 0;
		}

		*(float*)data = atof(argv[0]);
		return 0;
	};

	if (!sqlexec(
		"SELECT statistics.averageAnswerTime FROM statistics INNER JOIN users ON users.user_id = statistics.user_id WHERE users.name = \"" + username + "\" LIMIT 1;",
		callback,
		&averageAnswerTime
	))
	{
		throw SQLITE_DATABASE_ERROR;
	}
	return averageAnswerTime;
}

/// <summary>
/// getting from the database the num of correct answers of a player
/// </summary>
/// <param name="username">player username</param>
/// <returns>number of correct answers of a player</returns>
int SqliteDataBase::getNumOfCorrectAnswers(const std::string& username) const
{
	int numOfCorrectAnswers = 0;

	//callback function will assign query result to numOfCorrectAnswers
	auto callback = [](void* data, int argc, char** argv, char** azColName) -> int
	{
		if (argc == 0)
		{
			*(float*)data = 0;
			return 0;
		}

		*(int*)data = atoi(argv[0]);
		return 0;
	};

	if (!sqlexec(
		"SELECT statistics.numOfCorrectAnswers FROM statistics INNER JOIN users ON users.user_id = statistics.user_id WHERE users.name = \"" + username + "\" LIMIT 1;",
		callback,
		&numOfCorrectAnswers
	))
	{
		throw SQLITE_DATABASE_ERROR;
	}
	return numOfCorrectAnswers;
}

/// <summary>
/// getting from the database the is matching the username
/// </summary>
/// <param name="username">player username</param>
/// <returns>number of correct answers of a player</returns>
int SqliteDataBase::getUserId(const std::string& username) const
{
	int numOfCorrectAnswers = 0;

	//callback function will assign query result to numOfCorrectAnswers
	auto callback = [](void* data, int argc, char** argv, char** azColName) -> int
	{
		if (argc == 0)
		{
			*(float*)data = 0;
			return 0;
		}

		*(int*)data = atoi(argv[0]);
		return 0;
	};

	if (!sqlexec(
		"SELECT user_id FROM users WHERE users.name = \"" + username + "\" LIMIT 1;",
		callback,
		&numOfCorrectAnswers
	))
	{
		throw SQLITE_DATABASE_ERROR;
	}
	return numOfCorrectAnswers;
}

/// <summary>
/// getting from the database the num of total answers of a player
/// </summary>
/// <param name="username">player username</param>
/// <returns>number of total of a player</returns>
int SqliteDataBase::getNumOfTotalAnswers(const std::string& username) const
{
	int numOfTotalAnswers = 0;

	//callback function will assign query result to numOfTotalAnswers
	auto callback = [](void* data, int argc, char** argv, char** azColName) -> int
	{
		if (argc == 0)
		{
			*(float*)data = 0;
			return 0;
		}

		*(int*)data = atoi(argv[0]);
		return 0;
	};

	if (!sqlexec(
		"SELECT statistics.numOfTotalAnswers FROM statistics INNER JOIN users ON users.user_id = statistics.user_id WHERE users.name = \"" + username + "\" LIMIT 1;",
		callback,
		&numOfTotalAnswers
	))
	{
		throw SQLITE_DATABASE_ERROR;
	}
	return numOfTotalAnswers;
}

/// <summary>
/// getting from the database the num of player games
/// </summary>
/// <param name="username">player username</param>
/// <returns>number of player games</returns>
int SqliteDataBase::getNumOfPlayerGames(const std::string& username) const
{
	int numOfPlayerGames = 0;

	//callback function will assign query result to numOfPlayerGames
	auto callback = [](void* data, int argc, char** argv, char** azColName) -> int
	{
		if (argc == 0)
		{
			*(float*)data = 0;
			return 0;
		}

		*(int*)data = atoi(argv[0]);
		return 0;
	};

	if (!sqlexec(
		"SELECT statistics.numOfPlayerGames FROM statistics INNER JOIN users ON users.user_id = statistics.user_id WHERE users.name = \"" + username + "\" LIMIT 1;",
		callback,
		&numOfPlayerGames
	))
	{
		throw SQLITE_DATABASE_ERROR;
	}
	return numOfPlayerGames;
}

/// <summary>
/// Getting a vector of all questions in database
/// </summary>
/// <returns>all questions in database</returns>
std::queue<Question> SqliteDataBase::getQuestions() const
{
	std::queue<Question> questions;

	auto callback = [](void* data, int argc, char** argv, char** azColName) -> int
	{
		if (argc == 0)
			return 0;

		std::queue<Question>& questions = *(std::queue<Question>*)data;

		questions.push(
			Question(argv[0], { argv[1], argv[2], argv[3], argv[4] })
		);

		return 0;
	};

	if (!sqlexec(
		"SELECT question, correctAnswer, possibleAnswer1, possibleAnswer2, possibleAnswer3 FROM questions;", callback, &questions)
		|| questions.size() <= 0)
	{
		throw SQLITE_DATABASE_ERROR;
	}
	return questions;
}

/// <summary>
/// adds a question to the database
/// </summary>
/// <param name="question"></param>
/// <returns>status of operation</returns>
bool SqliteDataBase::addQuestion(const Question& question) const
{
	return sqlexec("INSERT INTO questions (question,correctanswer,possibleanswer1,possibleanswer2,possibleanswer3) VALUES(\"" +
		question.getQuestion() +
		"\" , \"" + question.getCorrectAnswer() +
		"\" , \"" + question.getPossibleAnswers()[1] +
		"\" , \"" + question.getPossibleAnswers()[2] +
		"\" , \"" + question.getPossibleAnswers()[3] +
		"\" );", nullptr, nullptr);
}

/// <summary>
/// retrives leaderboard from the database
/// </summary>
/// <returns>leaderboard stats</returns>
std::vector<std::string> SqliteDataBase::getLeaderboard() const
{
	std::vector<std::string> players;

	auto callback = [](void* data, int argc, char** argv, char** azColName) -> int
	{
		if (argc == 0)
			return 0;

		std::vector<std::string>& players = *(std::vector<std::string>*)data;

		//entering the amount of fields returned to the vector
		int count = 0;
		while (argv[count] != NULL && count <= (5 * 4)) //5 players where each one has 4 fields
		{
			players.push_back(argv[count++]);
		}
		return 0;
	};

	if (!sqlexec(
		"SELECT users.name, statistics.averageAnswerTime,statistics.numOfCorrectAnswers,statistics.numOfPlayerGames FROM statistics INNER JOIN users ON users.user_id = statistics.user_id LIMIT 5;",
		callback, &players))
	{
		throw SQLITE_DATABASE_ERROR;
	}

	return players;
}

bool SqliteDataBase::addUserStatistic(const PlayerResults& statistic) const
{
	int userId = getUserId(statistic.username);
	float averageTime = getPlayerAverageAnswerTime(statistic.username);
	int totalAnswers = getNumOfTotalAnswers(statistic.username);
	int correctAnswers = getNumOfCorrectAnswers(statistic.username);
	int playedGames = getNumOfPlayerGames(statistic.username);

	return sqlexec(
		"INSERT OR REPLACE INTO statistics "
		"(statistics_id, user_id, averageAnswerTime, numOfCorrectAnswers, numOfTotalAnswers, numOfPlayerGames) "
		"VALUES "
		"((SELECT statistics_id FROM statistics WHERE user_id = " + std::to_string(userId) + ")," +
		std::to_string(userId) + "," +
		std::to_string((totalAnswers * averageTime + (statistic.averageAnswerTime * (statistic.correctAnswerCount + statistic.wrongAnswerCount))) / (totalAnswers + (statistic.correctAnswerCount + statistic.wrongAnswerCount))) + "," +
		std::to_string(correctAnswers + statistic.correctAnswerCount) + "," +
		std::to_string(totalAnswers + statistic.correctAnswerCount + statistic.wrongAnswerCount) + "," +
		std::to_string(playedGames + 1) +
		");",
		nullptr,
		nullptr);
}