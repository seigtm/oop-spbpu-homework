// Baranov Konstantin Pavlovich, group v5130904/20021.
// STL. Lab #4, variant 2.

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

class factorial_iterator {
public:
    factorial_iterator(int number)
        : n{ number } {}

    int operator*() const {
        int factorial{ 1 };
        for(int i{ 2 }; i <= n; ++i)
            factorial *= i;
        return factorial;
    }

    factorial_iterator& operator++() {
        ++n;
        return *this;
    }

    factorial_iterator operator++(int) {
        auto temp{ *this };
        ++(*this);
        return temp;
    }

    factorial_iterator& operator--() {
        --n;
        return *this;
    }

    factorial_iterator operator--(int) {
        auto temp{ *this };
        --(*this);
        return temp;
    }

    bool operator==(const factorial_iterator& other) const {
        return n == other.n;
    }

    bool operator!=(const factorial_iterator& other) const {
        return !(*this == other);
    }

private:
    int n;
};

class factorial_container {
public:
    factorial_container() = default;

    factorial_iterator begin() const {
        return factorial_iterator{ 1 };
    }

    factorial_iterator end() const {
        return factorial_iterator{ 11 };
    }
};

int main() {
    factorial_container container;

    std::vector<int> result;
    std::copy(container.begin(), container.end(), std::back_inserter(result));

    std::cout << "Factorials from 1! to 10!: ";
    for(auto factorial : result)
        std::cout << factorial << ' ';
    std::cout << '\n';
}
