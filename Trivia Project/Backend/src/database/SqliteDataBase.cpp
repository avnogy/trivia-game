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
