#include <string>
#include <type_traits>
template <typename T>
concept ArithmeticOrString = std::is_arithmetic<typename T>

class Data {
   private:
	T value;

   public:
	Data() {}
};
