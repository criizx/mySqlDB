#include <queue>
#include <string>
#include <vector>

class Tokenizer {
   public:
	Tokenizer();
	~Tokenizer();

	// Splits string to tokens
	void Tokenize(const std::string& input);
	// Returns vector of tokens
	std::vector<std::string> GetTokens() const;

   private:
	std::vector<std::string> data;
};
