#pragma once
#pragma comment (lib, "ws2_32.lib")

#define VC_EXTRALEAN
#include <WinSock2.h>
#include <Windows.h>
#include <debugapi.h>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <map>
#include <ctime>
#include <cstdlib>

#include "utils/Singleton.h"

#define NONDEBUG_BASE_PATH "..\\..\\..\\"
#define DEBUG_BASE_PATH "..\\"

const std::string BASE_PATH = IsDebuggerPresent() ? DEBUG_BASE_PATH : NONDEBUG_BASE_PATH;

inline bool updateQuestions()
{
	try
	{
		return system(("python " + BASE_PATH + "opentdb-api\\opentdb_api.py " + BASE_PATH).c_str()) == 0;
	}
	catch (std::exception& e)
	{
		return false;
	}
}

inline bool createLockFile()
{
	try
	{
		return system(("python " + BASE_PATH + "opentdb-api\\create_lock.py " + BASE_PATH).c_str()) == 0;
	}
	catch (std::exception& e)
	{
		return false;
	}
}
