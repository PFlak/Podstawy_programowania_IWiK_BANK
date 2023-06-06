// Podstawy_programowania_IWiK_BANK.cpp : Defines the entry point for the application.
#include "Podstawy_programowania_IWiK_BANK.h"
#include <iostream>
#include "crow.h"
#include "ApiController.h"
#include "Logger.h"

// Tutaj będzie stało API oraz wszystkie metody stawiające bazy danych itp. itd.
int main() {
    crow::SimpleApp app;
    Logger log;
    log.makeLog("API_start", "api", false, "---");

    CROW_ROUTE(app, "/check")
        ([&log]() {
        return ApiController::statusCheck(log);
            });

    CROW_ROUTE(app, "/api/create_user").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {
        return ApiController::createUser(req, log);
            });

    CROW_ROUTE(app, "/api/login_user").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {
        return ApiController::loginUser(req, log);
            });

    CROW_ROUTE(app, "/api/logout_user").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {
        return ApiController::logoutUser(req, log);
            });

    CROW_ROUTE(app, "/api/update_user").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {
        return ApiController::updateUser(req, log);
            });

    CROW_ROUTE(app, "/api/check_balance").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {
        return ApiController::checkBalance(req, log);
            });

    CROW_ROUTE(app, "/api/admin/get_all_users").methods(crow::HTTPMethod::GET)
        ([&log]() {
        return ApiController::getAllUsers(log);
            });

    CROW_ROUTE(app, "/api/transfer").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {
        
        return ApiController::transfer(req, log);
            });

    CROW_ROUTE(app, "/api/get_history/<string>").methods(crow::HTTPMethod::GET)
        ([&log](const std::string& account) {

        return ApiController::getHistory(account, log);
            });

    CROW_ROUTE(app, "/api/get_user_account").methods(crow::HTTPMethod::POST)
        ([&log](const crow::request& req) {
        return ApiController::getUserAccount(req, log);
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
