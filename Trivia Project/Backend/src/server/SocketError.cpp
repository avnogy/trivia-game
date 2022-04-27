#include "server/SocketError.h"

SocketError::SocketError(const std::string& errorMessage) noexcept :
	m_errorMessage("Socket Error: " + errorMessage)
{
}

const char* SocketError::what() const
{
	return m_errorMessage.c_str();
}