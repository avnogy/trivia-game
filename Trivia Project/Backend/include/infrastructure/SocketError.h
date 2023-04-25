#pragma once
#include <string>
#include <exception>

class SocketError : public std::exception
{
private:
	const std::string m_errorMessage;

public:
	SocketError(const std::string& errorMessage) noexcept;
	const char* what() const override;
};
