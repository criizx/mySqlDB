#include <iostream>

#include "parser.hpp"

void Parser::parse() {
	// opening file
	std::ifstream file(input_file);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << input_file << std::endl;
		return;
	}

	std::string current_request = "";
	std::string line;

	// joining full file in one string
	while (std::getline(file, line)) {
		current_request += line + " ";
		if (line.find(';') != std::string::npos) {  // end of sql request
			sql_requests.push_back(current_request);
			current_request.clear();
		}
	}
	file.close();

	if (sql_requests.empty()) {
		std::cerr << "No SQL found in file." << std::endl;
		return;
	}

	for (const std::string& query : sql_requests) {
		Tokenizer tokenizer;
		tokenizer.Tokenize(query);

		std::vector<std::string> tokens = tokenizer.GetTokens();

		std::cout << "Parsed SQL Query Tokens:" << std::endl;
		for (const std::string& token : tokens) {
			std::cout << "[" << token << "] ";
		}
		std::cout << std::endl;
	}
}
