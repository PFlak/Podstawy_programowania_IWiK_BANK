#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>


class Logger {
public:
	virtual void standardLog(std::string MethodName_, std::string UserName_, bool isError=false, std::string ErrorCode = "---");
};