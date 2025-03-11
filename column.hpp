#ifndef COLUMN_HPP
#define COLUMN_HPP

#include <iostream>
#include <vector>

// Base class for columns
class Column {
   public:
	virtual ~Column() = default;
	virtual void print_value() const = 0;
};

// Template class TypedColumn
template <typename T>
class TypedColumn : public Column {
   private:
	std::vector<T> values;

   public:
	void addValue(const T& value);
	void print_value() const override;
};

#include "column.tpp"

#endif
