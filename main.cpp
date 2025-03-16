#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "column.hpp"
#include "table.hpp"
#include "tools.hpp"

int main() {
	try {
		// Создаем таблицу с именем "test"
		Table table("test");

		// Добавляем колонки разных типов
		table.addColumn(new TypedColumn<std::string>("Name"));
		table.addColumn(new TypedColumn<int>("Age"));
		table.addColumn(new TypedColumn<double>("Score"));
		table.addColumn(new TypedColumn<bool>("Active"));

		// Создаем тестовые данные
		std::string name1 = "Alice";
		int age1 = 25;
		double score1 = 85.5;
		bool active1 = true;

		std::string name2 = "Bob";
		int age2 = 30;
		double score2 = 92.3;
		bool active2 = false;

		// Формируем строки для добавления
		std::vector<void*> row1 = {&name1, &age1, &score1, &active1};
		std::vector<void*> row2 = {&name2, &age2, &score2, &active2};

		// Добавляем строки в таблицу
		table.addRow(row1);
		table.addRow(row2);

		// Выводим таблицу
		std::cout << "Original table:" << std::endl;
		table.printTable();

		// Сохраняем и создаем бэкап
		table.flushTable();
		table.backupTable();
		std::cout << "\nTable saved and backup created" << std::endl;

		// Создаем новую таблицу для теста загрузки
		Table loadedTable("test_loaded");
		loadedTable.addColumn(new TypedColumn<std::string>("Name"));
		loadedTable.addColumn(new TypedColumn<int>("Age"));
		loadedTable.addColumn(new TypedColumn<double>("Score"));
		loadedTable.addColumn(new TypedColumn<bool>("Active"));

		// Загружаем данные из файла
		loadedTable.loadFromFile("test.tbl");

		// Выводим загруженную таблицу
		std::cout << "\nLoaded table:" << std::endl;
		loadedTable.printTable();

		// Проверяем получение значений
		std::cout << "\nTesting getValue:" << std::endl;

	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
