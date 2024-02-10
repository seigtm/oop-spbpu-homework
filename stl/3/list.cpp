// Baranov Konstantin Pavlovich, group v5130904/20021.
// STL. Lab #3.2.

#include <algorithm>
#include <list>
#include <iostream>
#include <random>
#include <ranges>

int main() {
    std::list<int> l;

    for(auto sz : { 0, 1, 2, 3, 4, 5, 7, 14 }) {
        l.clear();
        l.resize(sz);

        std::cout << "List size: " << l.size() << '\n';

        std::ranges::generate(l, [] {
            static std::default_random_engine gen{ std::random_device{}() };
            static std::uniform_int_distribution int_dist{ 0, 20 };

            return int_dist(gen);
        });

        std::cout << "List in straight order: ";
        for(auto i : l)
            std::cout << i << ' ';

        std::cout << "\nList in zigzag order:   ";
        auto begin{ l.begin() };
        auto end{ std::prev(l.end()) };
        for(std::size_t i{}; i < l.size() / 2; ++i)
            std::cout << *begin++ << ' ' << *end-- << ' ';

        // If the list has odd number of elements, print the last element.
        if(l.size() % 2 != 0)
            std::cout << *begin;

        std::cout << "\n\n";
    }
}
