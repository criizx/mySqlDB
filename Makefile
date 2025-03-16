# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic

# Имя исполняемого файла
TARGET = test_program

# Исходные файлы
SRCS = main.cpp table.cpp tools.cpp

# Объектные файлы (автоматически генерируются из исходных)
OBJS = $(SRCS:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Правило для компиляции каждого .cpp файла в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка собранных файлов
clean:
	rm -f $(OBJS) $(TARGET)

# Флаг для предотвращения конфликтов с одноименными файлами
.PHONY: all clean
