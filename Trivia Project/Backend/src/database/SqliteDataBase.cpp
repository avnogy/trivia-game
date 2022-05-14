#include "database/SqliteDataBase.h"
#include "database/DatabaseError.h"

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
		sqlexec(R"(
				CREATE TABLE users(
				person_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
				name TEXT NOT NULL,
				password TEXT NOT NULL,
				email TEXT NOT NULL);
			)");

		sqlexec(R"(
				CREATE TABLE rooms(
				room_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
				name TEXT NOT NULL,
				maxPlayers INTEGER NOT NULL,
				numOfQuestionsInGame INTEGER NOT NULL,
				timePerQuestion INTEGER NOT NULL,
				isActive INTEGER NOT NULL);
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
/// executes a statement on the database
/// </summary>
/// <param name="msg">
///		: contains the statement to be executed
/// </param>
/// <returns></returns>
bool SqliteDataBase::sqlexec(const std::string& msg)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(m_db, msg.c_str(), nullptr, nullptr, &errMessage);
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
		throw DatabaseError("Sql request failed.");
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
	int result = sqlite3_prepare_v2(m_db, ("SELECT * FROM users WHERE name = \"" + username + "\" AND password = " + password + "; ").c_str(), -1, &selectstmt, NULL);
	if (result == SQLITE_OK)
	{
		//if row was returned the password matches the user
		bool match = sqlite3_step(selectstmt) == SQLITE_ROW;
		sqlite3_finalize(selectstmt);
		return match;
	}
	else
	{
		throw DatabaseError("Sql request failed, Couldn't check password.");
	}
}

/// <summary>
/// adds a new user to the database
/// </summary>
/// <param name="username"></param>
/// <param name="password"></param>
/// <param name="email"></param>
void SqliteDataBase::addNewUser(const std::string& username, const std::string& password, const std::string& email)
{
	if (!sqlexec("INSERT INTO users (name,password,email) VALUES (\"" + username + "\"," + password + ",\"" + email + "\");"))
	{
		throw DatabaseError("Sql request failed, Couldn't add user");
	}
}