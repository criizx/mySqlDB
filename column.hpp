#ifndef COLUMN_HPP
#define COLUMN_HPP

#include <cstddef>
#include <iostream>
#include <streambuf>
#include <string>
#include <vector>

enum class ColumnType { STRING, INT, DOUBLE, FLOAT, BOOL, CHAR };

class Column {
   private:
	std::string name;

   protected:
	ColumnType column_type;

   public:
	Column(ColumnType type) : column_type(type) {}
	virtual ~Column() = default;

	virtual void printValue(size_t index) const = 0;
	virtual void addValue(const std::string&) = 0;
	virtual void addValueFromAny(const void* value) = 0;
	virtual std::string getValue(size_t index) const = 0;
	virtual void flushToDisk(const std::string& filename) const = 0;
	virtual void loadFromFile(const std::string& filename) = 0;
	std::string getName() const { return name; }
	ColumnType getColumnType() const { return column_type; }
};

// template class TypedColumn
template <typename T>
class TypedColumn : public Column {
   private:
	std::vector<T> values;

   public:
	TypedColumn();

	void addValue(const std::string& value) override;
	void addValueFromAny(const void* value) override;
	void printValue(size_t index) const override;
	std::string getValue(size_t index) const override;
	void flushToDisk(const std::string& filename) const override;
	void loadFromFile(const std::string& filename) override;
};

#include "column.tpp"

#endif
