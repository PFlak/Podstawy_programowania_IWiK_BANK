#include "Logger.h"

#define LogfileName "GMD_Log.txt"

void Logger::standardLog(std::string MethodName_, std::string UserName_, bool isError, std::string  ErrorCode ) {
	std::fstream file;
	if (!file.is_open()) {
		file.open(LogfileName, std::ios::app);
	}

	std::time_t currentTime = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &currentTime);
	std::string timeString = std::asctime(&localTime);
	timeString.erase(timeString.length() - 1);

	if (isError) {
		file << std::setw(20) << timeString << std::setw(15) << MethodName_ << std::setw(15) << std::setw(15) << UserName_ << std::setw(6) << "ERROR" << std::setw(3) << ErrorCode << std::endl;
	}
	else
	{
		file << std::setw(20) << timeString << std::setw(15) << MethodName_ << std::setw(15) << std::setw(15) << UserName_ << std::setw(6) << "OK" << std::setw(3) << ErrorCode << std::endl;
	}

	try {
		file.close();
	}
	catch (const std::ios_base::failure& e) {
		std::cerr << e.what() << '\n';
	}

}

/*
	USE CASE:

	class someClass : Logger {
public:
	int k;

	someClass(int k_): k(k_) {}

	void someFunction() {
		k++;
		this->standardLog("someFunction", "someUser");
	}
};
*/