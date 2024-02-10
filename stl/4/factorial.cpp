// Baranov Konstantin Pavlovich, group v5130904/20021.
// STL. Lab #4, variant 2.

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

class factorial_iterator {
public:
    factorial_iterator(int start, int fact)
        : current{ start }, factorial{ fact } {}

    int operator*() const {
        int result{ 1 };
        for(int i{ 2 }; i <= current; ++i)
            result *= i;
        return result;
    }

    factorial_iterator& operator++() {
        ++current;
        return *this;
    }

    factorial_iterator operator++(int) {
        factorial_iterator temp{ *this };
        ++(*this);
        return temp;
    }

    factorial_iterator& operator--() {
        --current;
        return *this;
    }

    factorial_iterator operator--(int) {
        factorial_iterator temp{ *this };
        --(*this);
        return temp;
    }

    bool operator==(const factorial_iterator& other) const {
        return current == other.current && factorial == other.factorial;
    }

    bool operator!=(const factorial_iterator& other) const {
        return !(*this == other);
    }

private:
    int current;
    int factorial;
};

class factorial_container {
public:
    factorial_container() = default;

    factorial_iterator begin() const {
        return factorial_iterator{ 1, 1 };
    }

    factorial_iterator end() const {
        return factorial_iterator{ 11, 1 };
    }
};

int main() {
    factorial_container container;

    std::vector<int> result;
    std::copy(container.begin(), container.end(), std::back_inserter(result));

    // Вывод результатов
    std::cout << "Factorials from 1! to 10!: ";
    for(int factorial : result) {
        std::cout << factorial << ' ';
    }
    std::cout << '\n';
}
