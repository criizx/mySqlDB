
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

void Table::saveTable(std::string filename) const {
	// Opening file for writing in binary mode
	std::ofstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		perror("Cannot open file for writing");
		return;
	}

	// 1. Writing amount of columns
	int columns_amount = static_cast<int>(columns.size());
	file.write(reinterpret_cast<const char*>(&columns_amount), sizeof(columns_amount));

	// 2. Writing metadata for each column: length of name, name, column type
	for (size_t i = 0; i < columns.size(); ++i) {
		std::string colName = columns[i]->getName();
		int name_length = static_cast<int>(colName.size());
		file.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
		file.write(colName.c_str(), name_length);

		int colType = static_cast<int>(columns[i]->getColumnType());
		file.write(reinterpret_cast<const char*>(&colType), sizeof(colType));
	}

	// 3. Writing amount of rows (assuming all columns have the same size)
	int rows = 0;
	if (!columns.empty()) {
		rows = static_cast<int>(columns[0]->getSize());
	}
	file.write(reinterpret_cast<const char*>(&rows), sizeof(rows));

	// 4. Writing data row by row:
	// For each row, for each column, write:
	// - length of string representation of value (int)
	// - value itself (without terminating character)
	for (int r = 0; r < rows; ++r) {
		for (size_t c = 0; c < columns.size(); ++c) {
			std::string value = columns[c]->getValue(r);
			int value_length = static_cast<int>(value.size());
			file.write(reinterpret_cast<const char*>(&value_length), sizeof(value_length));
			file.write(value.c_str(), value_length);
		}
	}

	file.close();
}

void Table::loadFromFile(std::string filename) {
	if (filename.empty()) {
		filename = this->name + ".tbl";
	}
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		perror("Cannot open file for reading");
		return;
	}

	// 1. Read the number of columns
	int columns_amount;
	file.read(reinterpret_cast<char*>(&columns_amount), sizeof(columns_amount));

	// 2. Skip metadata for each column:
	// For each column:
	//   - Read the length of the name, then skip the name
	//   - Read the column type (as int)
	for (int c = 0; c < columns_amount; ++c) {
		int name_length;
		file.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
		file.seekg(name_length, std::ios::cur);  // skip the name

		int colType;
		file.read(reinterpret_cast<char*>(&colType), sizeof(colType));  // read the type
	}

	// 3. Read the number of rows
	int rows_count;
	file.read(reinterpret_cast<char*>(&rows_count), sizeof(rows_count));

	// 4. Read data row by row:
	// For each row and for each column:
	//   - Read the length of the value
	//   - Read the value (bytes) into a string
	//   - Add the value to the corresponding column using addValue()
	for (int r = 0; r < rows_count; ++r) {
		for (size_t c = 0; c < columns.size(); ++c) {
			int value_length;
			file.read(reinterpret_cast<char*>(&value_length), sizeof(value_length));

			std::string cell;
			cell.resize(value_length);
			file.read(&cell[0], value_length);

			columns[c]->addValue(cell);
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

auto Table::getColumnsSize() const { return columns.size(); };

void Table::flushTable() const { saveTable(name + ".tbl"); }

void Table::backupTable() const {
	std::string time = getCurrentTimeAsString();
	std::string backup_filename = name + "_backup_" + time + ".tbl";

	saveTable(backup_filename);
}
