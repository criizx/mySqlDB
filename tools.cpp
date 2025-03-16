#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
