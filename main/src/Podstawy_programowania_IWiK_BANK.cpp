// Podstawy_programowania_IWiK_BANK.cpp : Defines the entry point for the application.
#include "Podstawy_programowania_IWiK_BANK.h"
#include <iostream>
#include "CreateTables.h"
#include "DatabaseConnection.h"
#include <sqlite3.h>
#include <crow.h>
#include "Logger.h"

// Tutaj będzie stało API oraz wszystkie metody stawiające bazy danych itp. itd.
int main() {
    crow::SimpleApp app;
    Logger log;
    log.makeLog("API_start", "api", false, "---");

    CROW_ROUTE(app, "/check")
        ([&log]() {
        log.makeLog("API_check", "unknown", false, "---");
        return "API Works!";
            });

    CROW_ROUTE(app, "/api/create_user").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {

        // Check is Content-Type is application/json
        if (req.get_header_value("Content-Type") != "application/json") {
            log.makeLog("api_create_user", "", true, "415");
            return crow::response(415);
        }

        // Parse the JSON body
        crow::json::rvalue body;
        try {
            body = crow::json::load(req.body);
        }
        catch (const std::exception& e) {
            log.makeLog("api_create_user", "", true, "405");
            return crow::response(405);
        }

        // Get values from request
        if (!body.has("email")) {
            log.makeLog("api_create_user", "", true, "400");
            return crow::response(400);
        }
        std::string email = body["email"].s();

        if (!body.has("password")) {
            log.makeLog("api_create_user", "", true, "400");
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
            });

    CROW_ROUTE(app, "/api///login_user").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {

        // Check is Content-Type is application/json
        if (req.get_header_value("Content-Type") != "application/json") {
            log.makeLog("api_//login_user", "", true, "415");
            return crow::response(415);
        }

        // Parse the JSON body
        crow::json::rvalue body;
        try {
            body = crow::json::load(req.body);
        }
        catch (const std::exception& e) {
            log.makeLog("api_//login_user", "", true, "405");
            return crow::response(405);
        }

        // Get values from request
        if (!body.has("email")) {
            log.makeLog("api_//login_user", "", true, "400");
            return crow::response(400);
        }
        std::string email = body["email"].s();

        if (!body.has("password")) {
            log.makeLog("api_//login_user", "", true, "400");
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
        responseJson["method"] = "//login_user";
        responseJson["status"] = "success";

        return crow::response(200, responseJson);
            });

    CROW_ROUTE(app, "/api///logout_user").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {
        // Check is Content-Type is application/json
        if (req.get_header_value("Content-Type") != "application/json") {
            log.makeLog("api_//logout_user", "", true, "415");
            return crow::response(415);
        }

        // Parse the JSON body
        crow::json::rvalue body;
        try {
            body = crow::json::load(req.body);
        }
        catch (const std::exception& e) {
            log.makeLog("api_//logout_user", "", true, "405");
            return crow::response(405);
        }

        // Get values from request
        if (!body.has("email")) {
            log.makeLog("api_//logout_user", "", true, "400");
            return crow::response(400);
        }
        std::string email = body["email"].s();

        if (!body.has("password")) {
            log.makeLog("api_//logout_user", "", true, "400");
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
        responseJson["method"] = "//logout_user";
        responseJson["status"] = "success";

        return crow::response(200, responseJson);
            });

    CROW_ROUTE(app, "/api/update_user").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {
        // Check is Content-Type is application/json
        if (req.get_header_value("Content-Type") != "application/json") {
            log.makeLog("api_update_user", "", true, "415");
            return crow::response(415);
        }

        // Parse the JSON body
        crow::json::rvalue body;
        try {
            body = crow::json::load(req.body);
        }
        catch (const std::exception& e) {
            log.makeLog("api_update_user", "", true, "405");
            return crow::response(405);
        }

        if (!body.has("email")) {
            log.makeLog("api_update_user", "", true, "400");
            return crow::response(400);
        }

        std::string email = body["email"].s();

        if (!body.has("password")) {
            log.makeLog("api_update_user", "", true, "400");
            return crow::response(400);
        }

        std::string password = body["password"].s();

        if (body.has("role")) {
            log.makeLog("api_update_user", "", true, "400");
            return crow::response(400);
        }
        std::string role = body["role"].s();
        /*
         * ...
         * ...
         * ...
         * In case of other parameters
         */

         // Process the request


         // Return something
        crow::json::wvalue responseJson;
        responseJson["method"] = "update_user";
        responseJson["status"] = "success";

        return crow::response(200, responseJson);
            });

    CROW_ROUTE(app, "/api/check_balance").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {
        // Check is Content-Type is application/json
        if (req.get_header_value("Content-Type") != "application/json") {
            log.makeLog("api_check_balance", "", true, "415");
            return crow::response(415);
        }

        // Parse the JSON body
        crow::json::rvalue body;
        try {
            body = crow::json::load(req.body);
        }
        catch (const std::exception& e) {
            log.makeLog("api_check_balance", "", true, "405");
            return crow::response(405);
        }

        if (!body.has("id")) {
            log.makeLog("api_check_balance", "", true, "400");
            return crow::response(400);
        }

        std::string id = body["id"].s();

        crow::json::wvalue responseJson;
        responseJson["method"] = "check_balance";
        responseJson["status"] = "success";

        return crow::response(200, responseJson);
            });

    CROW_ROUTE(app, "/api/admin/get_all_users").methods(crow::HTTPMethod::GET)
        ([&log](const crow::request& req) {
        // Check is Content-Type is application/json
        if (req.get_header_value("Content-Type") != "application/json") {
            log.makeLog("api_get_all_users", "", true, "415");
            return crow::response(415);
        }

        crow::json::wvalue responseJson;
        responseJson["method"] = "get_all_users";
        responseJson["status"] = "success";

        return crow::response(200, responseJson);
            });

    CROW_ROUTE(app, "/api/get_user_data/<string>").methods(crow::HTTPMethod::GET)
        ([&log](const std::string& user) {
        return "success";
            });

    CROW_ROUTE(app, "/api/transfer").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {
        // Check is Content-Type is application/json
        if (req.get_header_value("Content-Type") != "application/json") {
            log.makeLog("api_transfer", "", true, "415");
            return crow::response(415);
        }

        // Parse the JSON body
        crow::json::rvalue body;
        try {
            body = crow::json::load(req.body);
        }
        catch (const std::exception& e) {
            log.makeLog("api_transfer", "", true, "405");
            return crow::response(405);
        }

        if (!body.has("from")) {
            log.makeLog("api_transfer", "", true, "400");
            return crow::response(400);
        }

        std::string from = body["from"].s();

        if (!body.has("to")) {
            log.makeLog("api_transfer", "", true, "400");
            return crow::response(400);
        }

        std::string to = body["from"].s();

        if (!body.has("amount")) {
            log.makeLog("api_transfer", "", true, "400");
            return crow::response(400);
        }

        std::string amount = body["amount"].s();

        crow::json::wvalue responseJson;
        responseJson["method"] = "transfer";
        responseJson["status"] = "success";

        return crow::response(200, responseJson);
            });

    CROW_ROUTE(app, "/api/get_history/<string>").methods(crow::HTTPMethod::GET)
        ([&log](const std::string& account) {
        crow::json::wvalue responseJson;
        responseJson["method"] = "get_history";
        responseJson["status"] = "success";

        return crow::response(200, responseJson);
            });

    app.bindaddr("0.0.0.0").port(18080).multithreaded().run();

    /*  CROW RESPONSES

       100 Continue
       101 Switching Protocols

       200 OK
       201 Created
       202 Accepted
       203 Non-Authoritative Information
       204 No Content
       205 Reset Content
       206 Partial Content

       300 Multiple Choices
       301 Moved Permanently
       302 Found
       303 See Other
       304 Not Modified
       307 Temporary Redirect
       308 Permanent Redirect

       400 Bad Request
       401 Unauthorized
       403 Forbidden
       404 Not Found
       405 Method Not Allowed
       407 Proxy Authentication Required
       409 Conflict
       410 Gone
       413 Payload Too Large
       415 Unsupported Media Type
       416 Range Not Satisfiable
       417 Expectation Failed
       428 Precondition Required
       429 Too Many Requests
       451 Unavailable For Legal Reasons

       500 Internal Server Error
       501 Not Implemented
       502 Bad Gateway
       503 Service Unavailable
       504 Gateway Timeout
       506 Variant Also Negotiates
    */


}
