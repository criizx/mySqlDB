#ifndef TABLE_HPP
#define TABLE_HPP

#include <cstdio>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <typeinfo>
#include <vector>

#include "column.hpp"

class Table {
   public:
	Table(const std::string& name);
	~Table();

	void addColumn(Column* column);
	void addRow(const std::vector<void*>& row);

	void saveTable(std::string filename) const;
	void loadFromFile(std::string filename = "");
	void printTable() const;
	void flushTable() const;
	void backupTable() const;

	auto getValue(const std::string& columnName, int row) const;
	auto getValue(const int column, int row) const;
	auto getColumnsSize() const;
	int getColumnIndex(const std::string& columnName) const;

   private:
	std::string name;
	std::vector<Column*> columns;
	int next_id;
};

#endif
