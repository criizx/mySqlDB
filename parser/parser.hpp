#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "tokenizer/tokenizer.hpp"

class Parser {
   public:
	Parser(const std::string& file_input) : input_file(file_input) {}

	void parse();  // main func

   private:
	std::string input_file;
	std::vector<std::string> sql_requests;  // list of sql requests
};
