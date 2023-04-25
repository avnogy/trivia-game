#pragma once

#include <string>

class LoggedUser
{
private:
	const std::string m_username;

public:
	LoggedUser(const std::string& username);
	std::string getUsername() const;
	bool operator==(const LoggedUser& other) const;
};

/// <summary>
/// Used to hash the class into the unordered_set
/// </summary>
template<>
struct std::hash<LoggedUser>
{
	std::size_t operator () (const LoggedUser& loggedUser) const
	{
		return std::hash<std::string>()(loggedUser.getUsername());
	}
};