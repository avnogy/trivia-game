#include "infrastructure/database/DatabaseError.h"

DatabaseError::DatabaseError(const std::string& errorMessage) noexcept :
	m_errorMessage("Database Error: " + errorMessage)
{
}

const char* DatabaseError::what() const
{
	return m_errorMessage.c_str();
}