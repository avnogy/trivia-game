#pragma once
#include "utils/utils.h"
#include <cstdlib> 

bool updateQuestions()
{
	try
	{
		return system(("python {}opentdb-api\\opentdb_api.py {}"+BASE_PATH+BASE_PATH).c_str()) == 0;
	}
	catch (std::exception& e)
	{
		return false;
	}
}


