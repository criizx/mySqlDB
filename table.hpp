#ifndef TABLE_HPP
#define TABLE_HPP

#include <string>
#include <vector>

#include "column.hpp"

class Table {
   public:
	Table(const std::string& name);
	void addColumn(Column* column);
	void addRow(const std::vector<void*>& row);
	void flushToDisk(const std::string& filename) const;
	void loadFromFile(const std::string& filename);

   private:
	std::string name;
	std::vector<Column*> columns;
};

#endif
