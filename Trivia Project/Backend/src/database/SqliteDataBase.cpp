#include "database/SqliteDataBase.h"
#include "database/DatabaseError.h"

/// <summary>
/// creates a database instence
/// </summary>
/// <param name="databasePath"> </param>
/// <returns></returns>
SqliteDataBase::SqliteDataBase(const std::string& databasePath) :filePath(databasePath)
{
	//checking if can access file
	int doesFileExist = !_access(filePath.c_str(), ACCESS_CODE);

	//attempting database open
	int res = sqlite3_open(filePath.c_str(), &db);

	if (res != SQLITE_OK)
	{
		db = nullptr;
		throw DatabaseError("Failed to open Sqlite database.");
	}
	if (!doesFileExist)
	{
		sqlexec("CREATE TABLE users(person_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT NOT NULL, password TEXT NOT NULL, email TEXT NOT NULL);");
	}
}

/// <summary>
/// destructs the database instence
/// </summary>
SqliteDataBase::~SqliteDataBase()
{
	//closing database
	sqlite3_close(db);
	db = nullptr;
}

/// <summary>
/// executes a statement on the database
/// </summary>
/// <param name="msg">
///		: contains the statement to be executed
/// </param>
/// <returns></returns>
void SqliteDataBase::sqlexec(const std::string& msg)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, msg.c_str(), nullptr, nullptr, &errMessage);
	assert(res == SQLITE_OK);
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
	int result = sqlite3_prepare_v2(db, ("SELECT * FROM users WHERE name = " + username + ";").c_str(), -1, &selectstmt, NULL);
	if (result == SQLITE_OK)
	{
		//if row was returned the user exists
		bool found = sqlite3_step(selectstmt) == SQLITE_ROW;
		sqlite3_finalize(selectstmt);
		return found;
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
	int result = sqlite3_prepare_v2(db, ("SELECT * FROM users WHERE name = " + username + " AND password = " + password + "; ").c_str(), -1, &selectstmt, NULL);
	if (result == SQLITE_OK)
	{
		//if row was returned the password matches the user
		bool match = sqlite3_step(selectstmt) == SQLITE_ROW;
		sqlite3_finalize(selectstmt);
		return match;
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
	sqlexec("INSERT INTO users (name,password,email) VALUES (" + username + "," + password + "," + email + ");");
}