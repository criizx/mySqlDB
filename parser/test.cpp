#include <iostream>

#include "parser.hpp"

int main() {
	std::string filename = "test.sql";

	Parser parser(filename);
	parser.parse();

	return 0;
}
