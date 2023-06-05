#pragma once
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>


class Logger {
public:
    void makeLog(std::string MethodName_, std::string UserName_, bool isError, std::string ErrorCode);
};