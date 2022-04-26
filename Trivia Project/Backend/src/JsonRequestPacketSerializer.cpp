#include "JsonPacketSerializer.h"

Buffer JsonRequestPacketSerializer::serializeResponse(ErrorResponse response)
{
	return Buffer();
}

Buffer JsonRequestPacketSerializer::serializeResponse(LoginResponse response)
{
	return Buffer();
}

Buffer JsonRequestPacketSerializer::serializeResponse(SignupResponse response)
{
	return Buffer();
}