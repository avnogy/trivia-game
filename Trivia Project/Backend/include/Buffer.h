#pragma once

#include <vector>
#include <string>

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
	std::string message() const;

	std::vector<Byte> buffer() const;
};