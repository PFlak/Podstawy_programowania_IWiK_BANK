// Podstawy_programowania_IWiK_BANK.cpp : Defines the entry point for the application.

#include "Podstawy_programowania_IWiK_BANK.h"
#include <iostream>
#include "../../db/src/CreateTables.h"
#include "../../db/src/DatabaseConnection.h"
#include <sqlite3.h>
#include "crow.h"


int main(int argc, char* argv[])
{
   

    //API example method running on localhost:18080
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
        });

    app.port(18080).multithreaded().run();



}
