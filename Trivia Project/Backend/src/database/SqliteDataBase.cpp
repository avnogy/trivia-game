#include "database/SqliteDataBase.h"
#include "database/DatabaseError.h"

/// <summary>
/// creates a database instence
/// </summary>
/// <param name="databasePath"> </param>
/// <returns></returns>
SqliteDataBase::SqliteDataBase(std::string databasePath) :filePath(databasePath)
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
		sqlexec("CREATE TABLE USERS(PERSON_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, NAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);");

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
void SqliteDataBase::sqlexec(std::string msg)
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
bool SqliteDataBase::doesUserExist(std::string username)
{
	//preparing a statement so it can be checked 
	struct sqlite3_stmt* selectstmt;
	int result = sqlite3_prepare_v2(db, ("SELECT * FROM USERS WHERE NAME = " + username + ";").c_str(), -1, &selectstmt, NULL);
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
bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	//preparing a statement so it can be checked 
	struct sqlite3_stmt* selectstmt;
	int result = sqlite3_prepare_v2(db, ("SELECT * FROM USERS WHERE NAME = " + username + " AND PASSWORD = " + password + "; ").c_str(), -1, &selectstmt, NULL);
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
void SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	sqlexec("INSERT INTO USERS (NAME,PASSWORD,EMAIL) VALUES (" + username + "," + password + "," + email + ");");
}
