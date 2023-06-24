#pragma once
#pragma comment (lib, "ws2_32.lib")

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

#include "utils/Singleton.h"

#define NONDEBUG_BASE_PATH "..\\..\\..\\"
#define DEBUG_BASE_PATH "..\\"

const std::string BASE_PATH = IsDebuggerPresent() ? DEBUG_BASE_PATH : NONDEBUG_BASE_PATH;

