#pragma once
#include "utils/utils.h"
#include <cstdlib>

bool updateQuestions()
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
