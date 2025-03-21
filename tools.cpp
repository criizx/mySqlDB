
#include "tools.hpp"

// Join strings with a separator |
std::string joinStrings(const std::vector<std::string>& strings) {
	std::string result;
	for (size_t i = 0; i < strings.size(); ++i) {
		result += strings[i];
		if (i != strings.size() - 1) {
			result += " | ";
		}
	}
	return result;
}

std::string getCurrentTimeAsString() {
	// Get the current time
	auto now = std::chrono::system_clock::now();
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

	// Convert to tm structure for local time
	std::tm now_tm = *std::localtime(&now_time_t);

	// Use a stringstream to format the time as a string
	std::ostringstream oss;
	oss << std::put_time(&now_tm, "%H:%M:%S_%d-%m-%Y");

	return oss.str();
}

// My realisation of IsDigit
bool checkIsDigit(const std::string str) {
	for (int i = 0; i < str.size(); i++) {
		if (str[i] < 48 || str[i] > 57) {
			return false;
		}
	}

	return true;
}
