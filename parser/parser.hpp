#include <iostream>

class Parser {
   public:
	Parser(const std::string& file_input) : input_file(file_input) {}
	void parse();

   private:
	std::string input_file;
};
