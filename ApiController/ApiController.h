#pragma once
#include "crow.h"
#include "Logger.h"
#include "Domain.h"

using namespace std;

class ApiController
{
public:
	static string statusCheck(Logger logger);
	static crow::response createUser(const crow::request& req, Logger logger);
	static crow::response loginUser(const crow::request& req, Logger logger);
	static crow::response logoutUser(const crow::request& req, Logger logger);
	static crow::response updateUser(const crow::request& req, Logger logger);
	static crow::response checkBalance(const crow::request& req, Logger logger);
	static crow::response getAllUsers(Logger logger);
	static crow::response transfer(const crow::request& req, Logger logger);
	static crow::response getHistory(const std::string& account, Logger logger);
	static crow::response getUserAccount(const crow::request& req, Logger logger);
};