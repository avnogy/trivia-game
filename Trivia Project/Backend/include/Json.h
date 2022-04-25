#pragma once
#include "json.hpp"
#include <string>

//********   delete when classes are linked   ********
typedef loginRequest;
typedef signupRequest;
typedef ErrorResponse;
typedef LoginResponse;
typedef SignupResponse;
//********   delete when classes are linked   ********


class JsonRequestPacketDeserializer
{
public:
	JsonRequestPacketDeserializer();
	~JsonRequestPacketDeserializer();

	static loginRequest deserializeLoginRequest(std::string buffer);
	static signupRequest deserializeSignupRequest(std::string buffer);
};

class JsonResponsePacketSerializer
{
public:
	JsonResponsePacketSerializer();
	~JsonResponsePacketSerializer();

	static std::string serializeResponse(ErrorResponse response);
	static std::string serializeResponse(LoginResponse response);
	static std::string serializeResponse(SignupResponse response);
};