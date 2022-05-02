#pragma once 
#include "database/IDatabase.h"
#include "sqlite3.h"
#include <string>
#include <iostream>
#include <io.h>

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase();
	~SqliteDataBase();
	
	void sqlexec(std::string msg);

	bool doesUserExist(std::string username) override;
	bool doesPasswordMatch(std::string username, std::string password) override;
	void addNewUser(std::string username, std::string password, std::string email) override;
private:
	sqlite3* db;
	std::string filePath;
};