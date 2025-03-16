#ifndef COLUMN_HPP
#define COLUMN_HPP

#include <cstddef>
#include <iostream>
#include <streambuf>
#include <string>
#include <vector>

enum class ColumnType { STRING, INT, DOUBLE, FLOAT, BOOL, CHAR };

class Column {
   protected:
	std::string name;
	ColumnType column_type;

   public:
	Column(const std::string& name, ColumnType type) : name(name), column_type(type) {}
	virtual ~Column() = default;

	virtual void printValue(size_t index) const = 0;
	virtual void addValue(const std::string&) = 0;
	virtual void addValueFromAny(const void* value) = 0;
	virtual std::string getValue(size_t index) const = 0;
	virtual size_t getSize() const = 0;
	virtual void flushToDisk(const std::string& filename) const = 0;
	virtual void loadFromFile(const std::string& filename) = 0;
	virtual void readValue(std::istream& file) = 0;

	std::string getName() const { return name; }
	ColumnType getColumnType() const { return column_type; }
};

template <typename T>
class TypedColumn : public Column {
   private:
	std::vector<T> values;

   public:
	TypedColumn(const std::string& name);

	void readValue(std::istream& file) override;
	void addValue(const std::string& value) override;
	void addValueFromAny(const void* value) override;
	void printValue(size_t index) const override;
	size_t getSize() const override;
	std::string getValue(size_t index) const override;
	void flushToDisk(const std::string& filename) const override;
	void loadFromFile(const std::string& filename) override;
};

#include "column.tpp"

#endif
