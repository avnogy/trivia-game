#include "database/SqliteDataBase.h"
#include "database/DatabaseError.h"

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
		sqlexec("CREATE TABLE USERS(PERSON_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, USERNAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);");

	}
}

SqliteDataBase::~SqliteDataBase()
{
	sqlite3_close(db);
	db = nullptr;
}

void SqliteDataBase::sqlexec(std::string msg)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, msg.c_str(), nullptr, nullptr, &errMessage);
	assert(res == SQLITE_OK);

	//only for testing
	std::cout << res;
	//****************
}


bool SqliteDataBase::doesUserExist(std::string username)
{
	struct sqlite3_stmt* selectstmt;
	int result = sqlite3_prepare_v2(db, ("SELECT * FROM USERS WHERE USERNAME = " + username + ";").c_str(), -1, &selectstmt, NULL);
	if (result == SQLITE_OK)
	{
		bool found = sqlite3_step(selectstmt) == SQLITE_ROW; //if row was returned the user exists
		sqlite3_finalize(selectstmt);
		return found;
	}
}

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	struct sqlite3_stmt* selectstmt;
	int result = sqlite3_prepare_v2(db, ("SELECT * FROM USERS WHERE USERNAME = " + username + " AND PASSWORD = " + password + "; ").c_str(), -1, &selectstmt, NULL);
	if (result == SQLITE_OK)
	{
		bool match = sqlite3_step(selectstmt) == SQLITE_ROW;	//if row was returned the passwoed matches
		sqlite3_finalize(selectstmt);
		return match;
	}
}

void SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	sqlexec("INSERT INTO USERS (NAME,PASSWORD,EMAIL) VALUES (" + username + "," + password + "," + email + ");");
}
