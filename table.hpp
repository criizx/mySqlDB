#ifndef TABLE_HPP
#define TABLE_HPP

#include <string>
#include <vector>

#include "column.hpp"

class Table {
   public:
	Table(const std::string& name);
	~Table();

	void addColumn(Column* column);
	void addRow(const std::vector<void*>& row);
	void flushToDisk(const std::string& filename) const;
	void loadFromFile(const std::string& filename);
	void printTable() const;

	auto getValue(const std::string& columnName, int row) const;
	auto getValue(const int column, int row) const;
	int getColumnIndex(const std::string& columnName) const;

   private:
	std::string name;
	std::vector<Column*> columns;
	int next_id;
};

#endif
