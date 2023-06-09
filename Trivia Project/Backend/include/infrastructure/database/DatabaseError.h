#pragma once
#include <string>
#include <exception>

class DatabaseError : public std::exception
{
private:
	const std::string m_errorMessage;

public:
	DatabaseError(const std::string& errorMessage) noexcept;
	const char* what() const override;
};
