#pragma once
#include <vector>
#include <string>

struct RequestInfo
{
	using RequestId = int;
	using Ctime = char*;
	using Buffer = std::string;

	RequestId id;
	Ctime receivalTime;
	Buffer buffer;
};