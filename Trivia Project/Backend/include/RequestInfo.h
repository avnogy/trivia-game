#pragma once
#include <vector>

struct RequestInfo
{
	using RequestId = int;
	using ctime = char*;
	using Byte = unsigned char;

	RequestId id;
	ctime receivalTime;
	std::vector<Byte> buffer;
};