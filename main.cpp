#include <filesystem>  // C++17 filesystem API
#include <iostream>
#include <memory>
#include <vector>

#include "column.hpp"
#include "table.hpp"
#include "tools.hpp"

using namespace std;

int main() {
	// Create initial table with name "TestTable"
	Table testTable("TestTable");

	// Add additional columns to the table
	// (ID column is automatically added in the constructor)
	// Create a string column "name"
	testTable.addColumn(new TypedColumn<std::string>("name"));
	// Create an int column "age"
	testTable.addColumn(new TypedColumn<int>("age"));

	// Prepare data for rows (excluding ID column)
	// Each row should have (number of columns - 1) values.
	// Here we have 2 values per row: name and age.
	{
		// Row 1: name = "Alice", age = 30
		std::string name1 = "Alice";
		int age1 = 30;
		vector<void*> row1 = {&name1, &age1};
		testTable.addRow(row1);
	}
	{
		// Row 2: name = "Bob", age = 25
		std::string name2 = "Bob";
		int age2 = 25;
		vector<void*> row2 = {&name2, &age2};
		testTable.addRow(row2);
	}

	cout << "Original Table:" << endl;
	testTable.printTable();

	testTable.flushToDisk();
	cout << "Table flushed to disk as 'TestTable.tbl'" << endl;

	Table loadedTable("LoadedTable");
	loadedTable.addColumn(new TypedColumn<std::string>("name"));
	loadedTable.addColumn(new TypedColumn<int>("age"));
	loadedTable.loadFromFile("TestTable.tbl");
	cout << "Loaded Table from file:" << endl;
	loadedTable.printTable();

	return 0;
}
