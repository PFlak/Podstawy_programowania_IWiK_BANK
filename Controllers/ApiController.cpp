#include "ApiController.h"

std::string ApiController::statusCheck()
{
	return "API Works!";
}

crow::response ApiController::createUser(const crow::request& req)
{

    // Check is Content-Type is application/json
    if (req.get_header_value("Content-Type") != "application/json") {
        return crow::response(415);
    }

    // Parse the JSON body
    crow::json::rvalue body;
    try {
        body = crow::json::load(req.body);
    }
    catch (const std::exception& e) {
        return crow::response(405);
    }

    // Get values from request
    if (!body.has("email")) {
        return crow::response(400);
    }
    std::string email = body["email"].s();

    if (!body.has("password")) {
        return crow::response(400);
    }
    std::string password = body["password"].s();
    /*
     * ...
     * ...
     * ...
     * In case of other parameters
     */

     // Process the request


     // Return something
    crow::json::wvalue responseJson;
    responseJson["method"] = "create_user";
    responseJson["status"] = "success";

    return crow::response(200, responseJson);
}