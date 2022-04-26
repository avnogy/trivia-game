#include "Buffer.h"

/// <summary>
/// Constructs a new buffer
/// </summary>
/// <param name="status">status of the message</param>
/// <param name="message">message</param>
Buffer::Buffer(Status status, const std::string& message)
{
	//buffer protocol: <status - 1 byte><messageSize - 4 bytes><message xbytes>
	const int messageSize = message.size();

	//push status
	m_buffer.push_back(status);

	//push message size
	m_buffer.push_back(messageSize >> sizeof(Byte) * 3); //first byte
	m_buffer.push_back(messageSize >> sizeof(Byte) * 2); //second byte
	m_buffer.push_back(messageSize >> sizeof(Byte) * 1); //third byte
	m_buffer.push_back(messageSize >> sizeof(Byte) * 0); //fourth byte

	//push message
	for (const char& i : message)
	{
		m_buffer.push_back(i);
	}
}

Buffer::Buffer(const nlohmann::json& json)
{
	Buffer buffer(json["status"], json.dump());
	m_buffer = buffer.m_buffer;
}

/// <summary>
/// get the status of the message from the buffer
/// </summary>
/// <returns>status</returns>
Status Buffer::status() const
{
	return m_buffer[0];
}

/// <summary>
/// get the message from the buffer
/// </summary>
/// <returns>the message in the buffer</returns>
std::string Buffer::message() const
{
	std::string message;
	auto it = m_buffer.begin() + 2; //skip status and size

	for (it; it != m_buffer.end(); ++it)
	{
		message += *it;
	}

	return message;
}

/// <summary>
/// get the buffer as a buffer (containing status, messageSize and message)
/// </summary>
/// <returns>the buffer</returns>
std::vector<Byte> Buffer::buffer() const
{
	return m_buffer;
}