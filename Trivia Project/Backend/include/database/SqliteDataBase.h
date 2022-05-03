#pragma once 
#include "database/IDatabase.h"
#include "sqlite3.h"
#include <string>
#include <iostream>
#include <io.h>
#include <cassert>

#define ACCESS_CODE 6

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase(const std::string databasePath);
	~SqliteDataBase();

	void sqlexec(const std::string msg);

	bool doesUserExist(const std::string username) override;
	bool doesPasswordMatch(const std::string username, const std::string password) override;
	void addNewUser(const std::string username, const std::string password, const std::string email) override;
private:
	sqlite3* db;
	std::string filePath;
};