#include <fstream>
#include <iostream>
#include <string>

#include "parser.hpp"

void Parser::parse() {
	// Implementation of the parse function
	//
	std::ifstream file(input_file);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << input_file << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		for (char c : line) {
			std::cout << c;
		}
		std::cout << std::endl;
	}
}
