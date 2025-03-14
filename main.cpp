#include <iostream>
#include <string>
#include <vector>

#include "table.hpp"

int main() {
	// Создаём таблицу с именем "Users"
	Table usersTable("Users");

	// Добавляем столбцы
	usersTable.addColumn(new TypedColumn<std::string>("Name"));
	usersTable.addColumn(new TypedColumn<int>("Age"));
	usersTable.addColumn(new TypedColumn<std::string>("Email"));

	// Создаём данные для строк
	std::string name1 = "Alice";
	int age1 = 25;
	std::string email1 = "alice@example.com";

	std::string name2 = "Bob";
	int age2 = 30;
	std::string email2 = "bob@example.com";

	// Добавляем строки (id добавляется автоматически)
	usersTable.addRow({&name1, &age1, &email1});
	usersTable.addRow({&name2, &age2, &email2});

	// Выводим таблицу
	usersTable.printTable();

	return 0;
}
