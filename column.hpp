#ifndef COLUMN_HPP
#define COLUMN_HPP

#include <iostream>
#include <string>
#include <vector>

enum class ColumnType { STRING, INT, DOUBLE, FLOAT, BOOL, CHAR };

class Column {
   protected:
	ColumnType columnType;

   public:
	virtual ~Column() = default;

	virtual void printValue() const = 0;
	virtual void addValue(const std::string&) = 0;
	virtual void addValueFromAny(const void* value) = 0;
	virtual std::string getValue(size_t index) const = 0;
	virtual void flushToDisk(const std::string& filename) const = 0;
	virtual void loadFromFile(const std::string& filename) = 0;
	ColumnType getColumnType() const { return columnType; }
};

// Шаблонный класс TypedColumn
template <typename T>
class TypedColumn : public Column {
   private:
	std::vector<T> values;

   public:
	TypedColumn();

	void addValue(const std::string& value) override;
	void addValueFromAny(const void* value) override;
	void printValue() const override;
	std::string getValue(size_t index) const override;
	void flushToDisk(const std::string& filename) const override;
	void loadFromFile(const std::string& filename) override;
};

#include "column.tpp"

#endif
