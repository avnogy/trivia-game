#pragma once
#include "json.hpp"
#include <string>

//********   delete when classes are linked   ********
typedef loginRequest;
typedef signupRequest;
//********   delete when classes are linked   ********


class JsonRequestPacketDeserializer
{
public:
	JsonRequestPacketDeserializer();
	~JsonRequestPacketDeserializer();

	static loginRequest deserializeLoginRequest(std::string buffer);
	static signupRequest deserializeSignupRequest(std::string buffer);
};

