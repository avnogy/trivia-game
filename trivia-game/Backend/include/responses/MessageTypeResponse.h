#pragma once
#include <string>

struct MessageTypeResponse
{
	enum Type
	{
		CorrectAnswerResponse,
		GetGameResultsResponse
	};

	Type type;
	std::string message;
};