// Podstawy_programowania_IWiK_BANK.cpp : Defines the entry point for the application.

#include "Podstawy_programowania_IWiK_BANK.h"
#include <iostream>
#include "CreateTables.h"
#include "DatabaseConnection.h"
#include <sqlite3.h>
#include "crow.h"


int main(int argc, char* argv[])
{
   
    

    //API example method running on localhost:18080
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
        });

    app.bindaddr("0.0.0.0").port(18080).multithreaded().run();



}
