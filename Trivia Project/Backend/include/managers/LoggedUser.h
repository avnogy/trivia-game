#pragma once

#include <string>

class LoggedUser
{
private:
	const std::string m_username;

public:
	LoggedUser(const std::string& username);
	std::string getUsername() const;
};