#include <iostream>
#include <vector>

class Column {
   public:
	virtual ~Column() = default;
	virtual void print_value() const = 0;
};

template <typename T>
class TypedColumn : public Column {
   private:
	std::vector<T> values;

   public:
	void addValue(const T& value) { values.push_back(value); }

	void print_value() const override {
		for (const auto& v : values) {
			std::cout << v << " ";
		}
		std::cout << std::endl;
	}
};
