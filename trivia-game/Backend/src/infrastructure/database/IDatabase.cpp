#include "infrastructure/database/IDatabase.h"
#include "infrastructure/database/SqliteDataBase.h"
#include "utils/utils.h"

//IDatabase* IDatabase::m_instance = new SqliteDataBase(std::format("{}bin\\database.sqlite",BASE_PATH));
IDatabase* IDatabase::m_instance = new SqliteDataBase(BASE_PATH + "bin\\database.sqlite");

IDatabase* IDatabase::instance()
{
	return m_instance;
}