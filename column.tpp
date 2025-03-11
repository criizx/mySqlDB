#ifndef COLUMN_TPP
#define COLUMN_TPP

// addValue method
template <typename T>
void TypedColumn<T>::addValue(const T& value) {
    values.push_back(value);
}

// print_value method
template <typename T>
void TypedColumn<T>::print_value() const {
    for (const auto& v : values) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

#endif // COLUMN_TPP
