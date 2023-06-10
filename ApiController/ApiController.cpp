#include "ApiController.h"
#include "Logger.h"
#include "Operations.h"
#include "UserFactory.h"
#include "AdminFactory.h"
#include "CustomerFactory.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string ApiController::statusCheck(Logger logger)
{
    logger.makeLog("api_check", "", false, "---");
	return "API Works!";
}

crow::response ApiController::UserController::createUser(const crow::request& req, Logger logger)
{
    // Check is Content-Type is application/json
    if (req.get_header_value("Content-Type") != "application/json") {
        logger.makeLog("api_create_user", "", true, "415");
        return crow::response(415);
    }
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
    std::string mail = body["email"].s();

    if (!body.has("password")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string password = body["password"].s();

    if (!body.has("name")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string name = body["name"].s();

    if (!body.has("surname")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string surname = body["surname"].s();

    if (!body.has("personalCode")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string personalCode = body["personalCode"].s();

    if (!body.has("phoneNumber")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string phoneNumber = body["phoneNumber"].s();

    if (!body.has("isEmployee")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string isEmployee = body["isEmployee"].s();

    UserFactory* factory;
    if (isEmployee == "true")
    {
        factory = new AdminFactory();
    }
    else
    {
        factory = new CustomerFactory();
    }
     
    Operations operations = OperationFactory::CreateOperations();
    bool success = operations.createUser(
        password,
        name,
        surname,
        personalCode,
        mail,
        phoneNumber, 
        factory);
    
    crow::json::wvalue responseJson;
    int status_code;
    if (success)
    {
        User user = operations.getUserByMail(mail);
        Account account1;
        Account account2;
        Account account3;
        account1.userId = user.id;
        account2.userId = user.id;
        account3.userId = user.id;
        account1.currency = "PLN";
        account2.currency = "PLN";
        account3.currency = "EUR";
        account1.type = "konto g³ówne";
        account2.type = "konto oszczêdnoœciowe";
        account3.type = "konto walutowe";
        account1.interestRate = 1;
        account2.interestRate = 2;
        account3.interestRate = 1;

        operations.createAccount(account1);
        operations.createAccount(account2);
        operations.createAccount(account3);

        responseJson["status"] = "ok";
        status_code = 200;
    }
    else
    {
        responseJson["status"] = "error";
        status_code = 500;
    }

    return crow::response(status_code, responseJson);
}

crow::response ApiController::UserController::loginUser(const crow::request& req, Logger logger)
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
    Operations operations = OperationFactory::CreateOperations();
    User user = operations.getUserByMail(email);
    crow::json::wvalue responseJson;
    int status_code;
    if (user.password == password)
    {
        responseJson["status"] = "ok";
        status_code = 200;
        if (user.isEmployee)
        {
            responseJson["role"] = "ADMIN";

        }
        else
        {
            responseJson["role"] = "customer";
        }
    }
    else
    {
        responseJson["status"] = "error";
        status_code = 401;
    }

    return crow::response(status_code, responseJson);
}

crow::response ApiController::UserController::logoutUser(const crow::request& req, Logger logger) {
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

crow::response ApiController::UserController::updateUser(const crow::request& req, Logger logger) {
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
    if (!body.has("email")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string mail = body["email"].s();

    if (!body.has("password")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string password = body["password"].s();

    if (!body.has("name")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string name = body["name"].s();

    if (!body.has("surname")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string surname = body["surname"].s();

    if (!body.has("personalCode")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string personalCode = body["personalCode"].s();

    if (!body.has("phoneNumber")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string phoneNumber = body["phoneNumber"].s();

    if (!body.has("isEmployee")) {
        logger.makeLog("api_create_user", "", true, "400");
        return crow::response(400);
    }
    std::string isEmployee = body["isEmployee"].s();

    UserFactory* factory;
    if (isEmployee == "true")
    {
        factory = new AdminFactory();
    }
    else
    {
        factory = new CustomerFactory();
    }

    Operations operations = OperationFactory::CreateOperations();
    bool success = operations.updateUser(
        password,
        name,
        surname,
        personalCode,
        mail,
        phoneNumber,
        factory);

    // Return something
    // Fixed for tests
    crow::json::wvalue responseJson;
    int status_code;
    if (success)
    {
        responseJson["status"] = "ok";
        status_code = 200;
    }
    else
    {
        responseJson["status"] = "error";
        status_code = 400;
    }

    return crow::response(status_code, responseJson);
}

crow::response ApiController::AccountController::checkBalance(const crow::request& req, Logger logger) {
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

crow::response ApiController::UserController::getAllUsers(Logger logger) {
    Operations operations = OperationFactory::CreateOperations();
    vector<User> users = operations.getAllUsers();
    json serializedVector;
    for (const auto& user : users)
    {
        json item;
        item["id"] = user.id;
        item["password"] = user.password;
        item["name"] = user.name;
        item["surname"] = user.surname;
        item["personalCode"] = user.personalCode;
        item["mail"] = user.mail;
        item["phoneNumber"] = user.phoneNumber;
        item["isEmployee"] = user.isEmployee;
        serializedVector.push_back(item);
    }

    std::string jsonString = serializedVector.dump();
    crow::json::wvalue responseJson;
    responseJson["status"] = "ok";
    responseJson["users"] = jsonString;
    return crow::response(200, responseJson);
}

crow::response ApiController::AccountController::transfer(const crow::request& req, Logger logger) {
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

crow::response ApiController::AccountController::getHistory(const std::string& account, Logger logger) {
    crow::json::wvalue responseJson;
    responseJson["status"] = "ok";
    // responseJson["history"] = { {{"from", "43 2423 4325 2355 5253"}, {"to", "57 5311 1111 1111"},{"amount", 21}}, {{"from", "43 2423 4325 2355 5253"}, {"to", "57 5311 1111 1112"},{"amount", 37}}};


    return crow::response(200, responseJson);
}

crow::response ApiController::AccountController::getUserAccount(const crow::request& req, Logger logger) {
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

    Operations operations = OperationFactory::CreateOperations();
    User user = operations.getUserByMail(email);

    vector<Account> accounts = operations.GetUserAccounts(user.id);
    json serializedVector;
    for (const auto& account : accounts)
    {
        json item;
        item["account_number"] = account.accountNumber;
        item["userId"] = account.userId;
        item["currency"] = account.currency;
        item["balance"] = account.balance;
        item["type"] = account.type;
        item["interestRate"] = account.interestRate;
        serializedVector.push_back(item);
    }

    std::string jsonString = serializedVector.dump();
    crow::json::wvalue responseJson;
    responseJson["status"] = "ok";
    responseJson["account"] = jsonString;
    return responseJson;

}