#include "column.hpp"
#include "table.hpp"

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
		std::string colFilename = filename + "_col" + std::to_string(i) + ".txt";
		columns[i]->flushToDisk(colFilename);
	}
}

void Table::loadFromFile(const std::string& filename) {
	for (size_t i = 0; i < columns.size(); ++i) {
		std::string colFilename = filename + "_col" + std::to_string(i) + ".txt";
		columns[i]->loadFromFile(colFilename);
	}
}
