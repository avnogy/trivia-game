#include "infrastructure/database/IDatabase.h"
#include "infrastructure/database/SqliteDataBase.h"
#include <Windows.h>
#include <debugapi.h>

IDatabase* IDatabase::m_instance = new SqliteDataBase(IsDebuggerPresent() ? DEBUG_DATABASE_FILE_PATH : DATABASE_FILE_PATH);

IDatabase* IDatabase::instance()
{
	return m_instance;
}