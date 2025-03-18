#include <cctype>

#include "tokenizer.hpp"

Tokenizer::Tokenizer() {}

Tokenizer::~Tokenizer() {}

void Tokenizer::Tokenize(const std::string& input) {
	data.clear();
	std::string token;
	bool in_quote = false;
	char quote_char = '\0';

	for (size_t i = 0; i < input.size(); ++i) {
		char ch = input[i];

		if (in_quote) {
			// if inside a quote
			if (ch == quote_char) {
				in_quote = false;
				data.push_back(token);
				token.clear();
			} else {
				token.push_back(ch);
			}
		} else {
			// if not inside a quote
			if (std::isspace(ch)) {
				if (!token.empty()) {
					data.push_back(token);
					token.clear();
				}
			} else if (ch == '\'' || ch == '\"') {
				// Start of quote
				if (!token.empty()) {
					data.push_back(token);
					token.clear();
				}
				in_quote = true;
				quote_char = ch;
			} else if (std::ispunct(ch)) {
				if (!token.empty()) {
					data.push_back(token);
					token.clear();
				}
				// 2 symb operators
				if (i + 1 < input.size() && (ch == '>' || ch == '<' || ch == '!' || ch == '=') && input[i + 1] == '=') {
					data.push_back(std::string(1, ch) + input[i + 1]);
					++i;
				} else {
					data.push_back(std::string(1, ch));
				}
			} else {
				token.push_back(ch);
			}
		}
	}
	if (!token.empty()) {
		data.push_back(token);
	}
}

std::vector<std::string> Tokenizer::GetTokens() const { return data; }
