#include "database/SqliteDataBase.h"

SqliteDataBase::SqliteDataBase(std::string databasePath) :filePath(databasePath)
{
	//checking if can access file
	int doesFileExist = !_access(filePath.c_str(), ACCESS_CODE); 

	//attempting database open 
	int res = sqlite3_open(filePath.c_str(), &db); 

	if (res != SQLITE_OK)
	{
		db = nullptr;
		//TODO: throw exception
	}
	if (!doesFileExist)
	{
		//create table
	}
}
