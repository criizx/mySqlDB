#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <typeinfo>

#include "column.hpp"
#include "table.hpp"
#include "tools.hpp"

Table::Table(const std::string& name) : name(name), next_id(1) {
	columns.push_back(new TypedColumn<int>("id"));
	std::ofstream outfile(name + ".tbl");
	if (!outfile.is_open()) {
		throw std::runtime_error("Ошибка: не удалось создать файл " + name);
	}
	outfile.close();
}

Table::~Table() {
	for (auto col : columns) {
		delete col;
	}
}

void Table::addColumn(Column* column) { columns.push_back(column); }

void Table::addRow(const std::vector<void*>& row) {
	if (row.size() != columns.size() - 1) {
		throw std::invalid_argument("Row size does not match column count (excluding id)");
	}

	int id = next_id++;
	columns[0]->addValueFromAny(&id);

	for (size_t i = 0; i < row.size(); ++i) {
		switch (columns[i + 1]->getColumnType()) {
			case ColumnType::STRING:
				columns[i + 1]->addValue(*static_cast<const std::string*>(row[i]));
				break;
			default:
				columns[i + 1]->addValueFromAny(row[i]);
				break;
		}
	}
}

void Table::flushToDisk() const {
	// opening file in binary format
	std::ofstream file(name + ".tbl", std::ios::binary);
	if (!file.is_open()) {
		perror("Cannot open file\n");
		return;
	}

	// (1) writing header of file

	// writing column amount
	int columns_amount = static_cast<int>(columns.size());
	file.write(reinterpret_cast<const char*>(&columns_amount), sizeof(columns_amount));

	// writing name + type for every column
	for (size_t i = 0; i < static_cast<size_t>(columns_amount); ++i) {
		std::string colName = columns[i]->getName();
		int name_length = static_cast<int>(colName.size());
		file.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
		file.write(colName.c_str(), name_length);

		int colType = static_cast<int>(columns[i]->getColumnType());
		file.write(reinterpret_cast<const char*>(&colType), sizeof(colType));
	}

	// (2) writing data for every column
	int rows = 0;
	if (!columns.empty()) {
		rows = static_cast<int>(columns[0]->getSize());
	}
	file.write(reinterpret_cast<const char*>(&rows), sizeof(rows));

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < columns_amount; ++c) {
			std::string value = columns[c]->getValue(r);
			int value_length = static_cast<int>(value.size());
			file.write(reinterpret_cast<const char*>(&value_length), sizeof(value_length));
			file.write(value.c_str(), value_length);
		}
	}

	file.close();
}

void Table::loadFromFile() {
	// opening file
	std::string filename = name + ".tbl";
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		perror("Cannot open file");
		return;
	}

	// reading columns amount
	int columns_amout;
	file.read(reinterpret_cast<char*>(&columns_amout), sizeof(columns_amout));
	for (int c = 0; c < columns_amout; ++c) {
		// skiping columns names
		int name_length;
		file.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
		file.seekg(name_length, std::ios::cur);
		// skiping columns types
		int type_length;
		file.read(reinterpret_cast<char*>(&type_length), sizeof(type_length));
		file.seekg(type_length, std::ios::cur);
	}
	int rows_count;
	file.read(reinterpret_cast<char*>(&rows_count), sizeof(rows_count));

	for (int r = 0; r < rows_count; ++r) {
		for (int c = 0; c < columns_amout; ++c) {
			columns[c]->readValue(file);
		}
	}
	file.close();
}

void Table::printTable() const {
	std::vector<std::string> column_names;
	for (size_t i = 0; i < columns.size(); ++i) {
		column_names.push_back(columns[i]->getName());
	}
	std::cout << joinStrings(column_names) << std::endl;
	for (size_t j = 0; j < columns[0]->getSize(); ++j) {
		for (size_t i = 0; i < columns.size(); ++i) {
			columns[i]->printValue(j);
		}
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
