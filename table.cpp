#include "column.hpp"
#include "table.hpp"
#include "tools.hpp"

Table::Table(const std::string& name) : name(name) {}

void Table::addColumn(Column* column) { columns.push_back(column); }

void Table::addRow(const std::vector<void*>& row) {
	if (row.size() != columns.size()) {
		throw std::invalid_argument("Row size does not match column count");
	}

	for (size_t i = 0; i < row.size(); ++i) {
		switch (columns[i]->getColumnType()) {
			case ColumnType::STRING:
				columns[i]->addValue(*static_cast<const std::string*>(row[i]));
				break;
			default:
				columns[i]->addValueFromAny(row[i]);
				break;
		}
	}
}

void Table::flushToDisk(const std::string& filename) const {
	for (size_t i = 0; i < columns.size(); ++i) {
		std::string col_filename = filename + "_col" + std::to_string(i) + ".txt";
		columns[i]->flushToDisk(col_filename);
	}
}

void Table::loadFromFile(const std::string& filename) {
	for (size_t i = 0; i < columns.size(); ++i) {
		std::string col_filename = filename + "_col" + std::to_string(i) + ".txt";
		columns[i]->loadFromFile(col_filename);
	}
}

void Table::printTable() const {
	std::vector<std::string> column_names;
	for (size_t i = 0; i < columns.size(); ++i) {
		column_names.push_back(columns[i]->getName());
	}
	std::cout << joinStrings(column_names) << std::endl;
	for (size_t i = 0; i < columns.size(); ++i) {
		columns[i]->printValue(i);
		std::cout << std::endl;
	}
}

int Table::getColumnIndex(const std::string& columnName) const {
	for (size_t i = 0; i < columns.size(); ++i) {
		if (columns[i]->getName() == columnName) {
			return i;
		}
	}
	throw std::invalid_argument("Column not found");
}

auto Table::getValue(const std::string& columnName, int row) const {
	return columns[getColumnIndex(columnName)]->getValue(row);
}
auto Table::getValue(const int column, int row) const { return columns[column]->getValue(row); }
