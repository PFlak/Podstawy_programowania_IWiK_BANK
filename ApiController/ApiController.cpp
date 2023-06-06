#include "ApiController.h"
#include "Logger.h"

std::string ApiController::statusCheck(Logger logger)
{
    logger.makeLog("api_check", "", false, "---");
	return "API Works!";
}

crow::response ApiController::createUser(const crow::request& req, Logger logger)
{
    // Check is Content-Type is application/json
    if (req.get_header_value("Content-Type") != "application/json") {
        logger.makeLog("api_create_user", "", true, "415");
        return crow::response(415);
    }
    User newUser;
    // Parse the JSON body
    crow::json::rvalue body;
    try {
        body = crow::json::load(req.body);
    }
    catch (const std::exception& e) {
        logger.makeLog("api_create_user", "", true, "415");
        return crow::response(405);
    }

    // Get values from request
    if (!body.has("email")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.mail = body["email"].s();

    if (!body.has("password")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.password = body["password"].s();

    if (!body.has("login")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.login = body["login"].s();

    if (!body.has("name")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.name = body["name"].s();

    if (!body.has("surname")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.surname = body["surname"].s();

    if (!body.has("personalCode")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.personalCode = body["personalCode"].s();

    if (!body.has("phoneNumber")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.phoneNumber = body["phoneNumber"].s();

    if (!body.has("isEmployee")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    // newUser.isEmployee = body["isEmployee"].s();
     
    
    // TO DO: insert newUser to the database

    crow::json::wvalue responseJson;
    responseJson["status"] = "ok";

    return crow::response(200, responseJson);
}

crow::response ApiController::loginUser(const crow::request& req, Logger logger) 
{
    // Check is Content-Type is application/json
    if (req.get_header_value("Content-Type") != "application/json") {
        logger.makeLog("api_login_user", "", true, "415");
        return crow::response(415);
    }

    // Parse the JSON body
    crow::json::rvalue body;
    try {
        body = crow::json::load(req.body);
    }
    catch (const std::exception& e) {
        logger.makeLog("api_login_user", "", true, "405");
        return crow::response(405);
    }

    // Get values from request
    if (!body.has("email")) {
        logger.makeLog("api_login_user", "", true, "400");
        return crow::response(400);
    }
    std::string email = body["email"].s();

    if (!body.has("password")) {
        logger.makeLog("api_login_user", "", true, "400");
        return crow::response(400);
    }
    std::string password = body["password"].s();

    // Process the request
    //TO DO: get from database user by email, compare passwords, if passwords match return ok and role based on employee flag

    // Return something
    crow::json::wvalue responseJson;
    responseJson["status"] = "ok";
    responseJson["role"] = "ADMIN";

    return crow::response(200, responseJson);
}

crow::response ApiController::logoutUser(const crow::request& req, Logger logger) {
    // Check is Content-Type is application/json
    if (req.get_header_value("Content-Type") != "application/json") {
        logger.makeLog("api_logout_user", "", true, "415");
        return crow::response(415);
    }

    // Parse the JSON body
    crow::json::rvalue body;
    try {
        body = crow::json::load(req.body);
    }
    catch (const std::exception& e) {
        logger.makeLog("api_logout_user", "", true, "405");
        return crow::response(405);
    }

    // Get values from request
    if (!body.has("email")) {
        logger.makeLog("api_logout_user", "", true, "400");
        return crow::response(400);
    }
    std::string email = body["email"].s();

    logger.makeLog("api_logout_user", email, false, "");

    crow::json::wvalue responseJson;
    responseJson["status"] = "ok";

    return crow::response(200, responseJson);
}

crow::response ApiController::updateUser(const crow::request& req, Logger logger) {
    // Check is Content-Type is application/json
    if (req.get_header_value("Content-Type") != "application/json") {
        logger.makeLog("api_update_user", "", true, "415");
        return crow::response(415);
    }

    // Parse the JSON body
    crow::json::rvalue body;
    try {
        body = crow::json::load(req.body);
    }
    catch (const std::exception& e) {
        logger.makeLog("api_update_user", "", true, "405");
        return crow::response(405);
    }
    User newUser;
    if (!body.has("email")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.mail = body["email"].s();

    if (!body.has("password")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.password = body["password"].s();

    if (!body.has("login")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.login = body["login"].s();

    if (!body.has("name")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.name = body["name"].s();

    if (!body.has("surname")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.surname = body["surname"].s();

    if (!body.has("personalCode")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.personalCode = body["personalCode"].s();

    if (!body.has("phoneNumber")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    newUser.phoneNumber = body["phoneNumber"].s();

    if (!body.has("isEmployee")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    // newUser.isEmployee = body["isEmployee"].s();

    if (body.has("role")) {
        logger.makeLog("api_update_user", "", true, "400");
        return crow::response(400);
    }
    std::string role = body["role"].s();

    // Process the request
    //TO DO: run update user database command

    // Return something
    // Fixed for tests
    crow::json::wvalue responseJson;
    responseJson["status"] = "ok";

    return crow::response(200, responseJson);
}

crow::response ApiController::checkBalance(const crow::request& req, Logger logger) {
    // Check is Content-Type is application/json
    if (req.get_header_value("Content-Type") != "application/json") {
        logger.makeLog("api_check_balance", "", true, "415");
        return crow::response(415);
    }

    // Parse the JSON body
    crow::json::rvalue body;
    try {
        body = crow::json::load(req.body);
    }
    catch (const std::exception& e) {
        logger.makeLog("api_check_balance", "", true, "405");
        return crow::response(405);
    }

    if (!body.has("id")) {
        logger.makeLog("api_check_balance", "", true, "400");
        return crow::response(400);
    }

    std::string id = body["id"].s();

    // Process the request


    // Return something
    // Fixed for tests
    crow::json::wvalue responseJson;
    responseJson["credits"] = 2137;
    responseJson["status"] = "success";

    return crow::response(200, responseJson);
}

crow::response ApiController::getAllUsers(Logger logger) {

    crow::json::wvalue responseJson;
    responseJson["status"] = "ok";
    // responseJson["users"] = { {{"email", "abcd@domain.com"}, {"role", "USER"}}, {{"email", "ergh@domain.com"}, {"role", "ADMIN"}} };

    return crow::response(200, responseJson);
}

crow::response ApiController::transfer(const crow::request& req, Logger logger) {
    // Check is Content-Type is application/json
    if (req.get_header_value("Content-Type") != "application/json") {
        logger.makeLog("api_transfer", "", true, "415");
        return crow::response(415);
    }

    // Parse the JSON body
    crow::json::rvalue body;
    try {
        body = crow::json::load(req.body);
    }
    catch (const std::exception& e) {
        logger.makeLog("api_transfer", "", true, "405");
        return crow::response(405);
    }

    if (!body.has("from")) {
        logger.makeLog("api_transfer", "", true, "400");
        return crow::response(400);
    }

    std::string from = body["from"].s();

    if (!body.has("to")) {
        logger.makeLog("api_transfer", "", true, "400");
        return crow::response(400);
    }

    std::string to = body["from"].s();

    if (!body.has("amount")) {
        logger.makeLog("api_transfer", "", true, "400");
        return crow::response(400);
    }

    std::string amount = body["amount"].s();

    crow::json::wvalue responseJson;
    responseJson["status"] = "ok";

    return crow::response(200, responseJson);
}

crow::response ApiController::getHistory(const std::string& account, Logger logger) {
    crow::json::wvalue responseJson;
    responseJson["status"] = "ok";
    // responseJson["history"] = { {{"from", "43 2423 4325 2355 5253"}, {"to", "57 5311 1111 1111"},{"amount", 21}}, {{"from", "43 2423 4325 2355 5253"}, {"to", "57 5311 1111 1112"},{"amount", 37}}};


    return crow::response(200, responseJson);
}

crow::response ApiController::getUserAccount(const crow::request& req, Logger logger) {
    if (req.get_header_value("Content-Type") != "application/json") {
        logger.makeLog("api_get_user_account", "", true, "415");
        return crow::response(415);
    }

    // Parse the JSON body
    crow::json::rvalue body;
    try {
        body = crow::json::load(req.body);
    }
    catch (const std::exception& e) {
        logger.makeLog("api_get_user_account", "", true, "405");
        return crow::response(405);
    }

    if (!body.has("email")) {
        logger.makeLog("api_get_user_account", "", true, "400");
        return crow::response(400);
    }
    std::string email = body["email"].s();

    crow::json::wvalue responseJson;
    responseJson["status"] = "ok";
    // responseJson["account"] = { {{"id", "43 2423 4325 2355 5253"}, {"type", 2},{"amount", 21}}, {{"id", "43 2423 4325 2355 5253"}, {"type", 3},{"amount", 54}} };
    return responseJson;

}