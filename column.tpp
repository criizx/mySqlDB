#ifndef COLUMN_TPP
#define COLUMN_TPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <stdexcept>

// adding value from string
template <typename T>
void TypedColumn<T>::addValue(const std::string& value) {
	std::istringstream iss(value);
	T converted_value;
	if (!(iss >> converted_value)) {
		throw std::invalid_argument("Invalid data format for column type");
	}
	values.push_back(converted_value);
}

// getting size of column
template <typename T>
size_t TypedColumn<T>::getSize() const {
	return values.size();
}

// universal method for adding value from any type
template <typename T>
void TypedColumn<T>::addValueFromAny(const void* value) {
	if (!value) throw std::invalid_argument("Null pointer passed to addValueFromAny");
	values.push_back(*static_cast<const T*>(value));
}

// printing values
template <typename T>
void TypedColumn<T>::printValue(size_t index) const {
	if (index < values.size()) {
		std::cout << values[index] << " ";
	}
}

// getting value in string format
template <typename T>
std::string TypedColumn<T>::getValue(size_t index) const {
	if (index < values.size()) {
		std::ostringstream oss;
		oss << values[index];
		return oss.str();
	}
	throw std::out_of_range("Index out of range");
}

template <typename T>
TypedColumn<T>::TypedColumn(const std::string& name)
    : Column(name, [] {
          if constexpr (std::is_same_v<T, std::string>)
              return ColumnType::STRING;
          else if constexpr (std::is_same_v<T, int>)
              return ColumnType::INT;
          else if constexpr (std::is_same_v<T, double>)
              return ColumnType::DOUBLE;
          else if constexpr (std::is_same_v<T, bool>)
              return ColumnType::BOOL;
          else if constexpr (std::is_same_v<T, float>)
              return ColumnType::FLOAT;
          else if constexpr (std::is_same_v<T, char>)
              return ColumnType::CHAR;
          else
              throw std::invalid_argument("Unsupported column type");
      }()) {}

// saving data to file(Column)
template <typename T>
void TypedColumn<T>::flushToDisk(const std::string& filename) const {
	std::ofstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file for writing: " + filename);
	}
	for (const auto& v : values) {
		file << v << "\n";
	}
	file.close();
}

// loading data from file(Column)
template <typename T>
void TypedColumn<T>::loadFromFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file for reading: " + filename);
	}
	values.clear();
	T value;
	while (file >> value) {
		values.push_back(value);
	}
	file.close();
}

#endif  // COLUMN_TPP
