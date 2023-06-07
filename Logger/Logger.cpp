#include "Logger.h"

void Logger::makeLog(std::string MethodName_, std::string UserName_, bool isError, std::string  ErrorCode) {
    std::fstream file;
    if (!file.is_open()) {
        file.open("GMD_Log.txt", std::ios::app);
    }

    time_t currentTime = time(nullptr);
    char timeString[26];
    ctime_s(timeString, sizeof timeString, &currentTime);
    size_t newlinePos = std::strcspn(timeString, "\n");
    timeString[newlinePos] = '\0';

    if (isError) {
        file << std::setw(27) << timeString << std::setw(15) << MethodName_ << std::setw(15) << std::setw(15) << UserName_ << std::setw(6) << "ERROR" << std::setw(4) << ErrorCode << std::endl;
    }
    else
    {
        file << std::setw(27) << timeString << std::setw(15) << MethodName_ << std::setw(15) << std::setw(15) << UserName_ << std::setw(6) << "OK" << std::setw(4) << ErrorCode << std::endl;
    }

    try {
        file.close();
    }
    catch (const std::ios_base::failure& e) {
        std::cout << e.what() << '\n';
    }

}