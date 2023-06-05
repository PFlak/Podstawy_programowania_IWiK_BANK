#pragma once
#include "crow.h"

using namespace std;

class ApiController
{
public:
	static string statusCheck();
	static crow::response createUser(const crow::request& req);
	static crow::response loginUser(const crow::request& req, Logger logger);
};