#include "IDatabase.h"
#include "database/SqliteDataBase.h"

IDatabase* IDatabase::m_instance = new SqliteDataBase(DATABASE_FILE_PATH);

IDatabase* IDatabase::instance()
{
	return m_instance;
}