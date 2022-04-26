#pragma once

#include <vector>
#include <string>
#include "json.hpp"

typedef unsigned char Byte;
typedef unsigned char Status;

class Buffer
{
private:
	std::vector<Byte> m_buffer;

public:
	Buffer() = default;
	Buffer(Status status, const std::string& message);

	Status status() const;
	std::string content() const;
	std::vector<Byte> buffer() const;
};