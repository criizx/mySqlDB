#include <cstdio>
#include <string>
#include <vector>

#include "column.hpp"

class Table {
   public:
	Table(const std::string& name) : name(name) {}
	void addColumn(Column* column) { columns.push_back(column); }

   private:
	std::string name;
	std::vector<Column*> columns;
};
