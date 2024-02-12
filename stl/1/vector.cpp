// Baranov Konstantin Pavlovich, group v5130904/20021.
// STL. Lab #1.

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

#include <cxxopts.hpp>
#include <nanobench.h>

namespace tasks {

template<class T, class Pred = std::less<T>>
void insort_brackets(std::vector<T>& vec, Pred comp = Pred{}) {
    for(std::size_t current{ 1UZ }; current < vec.size(); ++current) {
        const T key{ vec[current] };
        std::size_t border{ current };

        // Move elements in vec[0..border-1] based on the provided comparison predicate 'comp', such that they are
        // ordered before the key
        while(border != 0 && comp(key, vec[border - 1])) {
            vec[border] = vec[border - 1];
            --border;
        }
        vec[border] = key;
    }
}

template<class T, class Pred = std::less<T>>
void insort_at(std::vector<T>& vec, Pred comp = Pred{}) {
    for(std::size_t current{ 1UZ }; current < vec.size(); ++current) {
        const int key{ vec.at(current) };
        std::size_t border{ current };

        // Move elements in vec[0..border-1] based on the provided comparison predicate 'comp', such that they are
        // ordered before the key
        while(border != 0 && comp(key, vec.at(border - 1))) {
            vec.at(border) = vec.at(border - 1);
            --border;
        }
        vec.at(border) = key;
    }
}

template<class Iterator, class Pred = std::less<>>
void insort_iter(Iterator first, Iterator last, Pred comp = Pred{}) {
    if(first == last) return;

    const auto rend{ std::make_reverse_iterator(first) };
    for(auto current{ std::next(first) }; current != last; ++current) {
        auto previous{ std::make_reverse_iterator(std::next(current)) };
        auto rnext{ std::next(previous) };
        while(rnext != rend && comp(*previous, *rnext)) {
            std::iter_swap(previous++, rnext++);
        }
    }
}

void fill_random(std::signed_integral auto* array, std::size_t size) {
    if(array == nullptr || size == 0) return;

    static std::default_random_engine gen{ std::random_device{}() };
    static std::uniform_int_distribution int_dist{ -1, 1 };

    std::generate(array, array + size, [] { return int_dist(gen); });
}

void fill_random(std::floating_point auto* array, std::size_t size) {
    if(array == nullptr || size == 0) return;

    static std::default_random_engine gen{ std::random_device{}() };
    static std::uniform_real_distribution real_dist{ -1.0, 1.0 };

    std::generate(array, array + size, [] { return real_dist(gen); });
}

}  // namespace tasks

int main(int argc, char** argv) {
    cxxopts::Options options("Lab1Vector", "Vector tasks");
    // clang-format off
    options.add_options()
        ("t,tests", "Run tests (tasks 1-3)", cxxopts::value<bool>()->default_value("false"))
        ("p,path", "Path to the file for task 4", cxxopts::value<std::string>()->default_value("data.txt"))
        ("h,help",  "Print usage");
    // clang-format on

    auto result{ options.parse(argc, argv) };
    if(result.count("help")) {
        std::cout << options.help() << '\n';
        std::exit(0);
    }
    const bool should_tests_run{ result["tests"].as<bool>() };
    const std::string filepath{ result["path"].as<std::string>() };

    std::vector<int> vec(10'000);
    tasks::fill_random(vec.data(), vec.size());

    if(should_tests_run) {
        ankerl::nanobench::Bench bench;
        // Need a copy of that vector for tests to be fairly comparable.
        std::vector<int> numbers;

        // 1. Implement the sorting algorithm for the vector of integers using the std::vector<>::operator[].
        bench.run("Insertion sort w/ operator[]", [&]() {
            numbers = vec;
            tasks::insort_brackets(numbers);
        });

        // 2. Implement the sorting algorithm for the vector of integers using the std::vector<>::at() method.
        bench.run("Insertion sort w/ .at()", [&]() {
            numbers = vec;
            tasks::insort_at(numbers);
        });

        // 3. Implement the sorting algorithm for the vector of integers using only iterators.
        //    Use only the get and advance iterator operations.
        bench.run("Insertion sort w/ iterators", [&]() {
            numbers = vec;
            tasks::insort_iter(numbers.begin(), numbers.end());
        });
    }

    // 4. Read the contents of the C-style array from a text file, and copy the data to the vector one line at a time
    //    (without loops and STL algorithms).
    std::ifstream ifs{ filepath };
    if(!ifs) {
        std::cerr << "Error opening file\n";
        std::exit(EXIT_FAILURE);
    }

    ifs.seekg(0, std::ios::end);
    const std::size_t size{ static_cast<std::size_t>(ifs.tellg()) };
    char* c_arr{ new char[size] };

    ifs.seekg(0);
    ifs.read(c_arr, size);

    std::vector<char> vec_from_c_arr{ c_arr, c_arr + size };
    // Alternative: vec_from_c_arr.assign(c_arr, c_arr + size);
    delete[] c_arr;

    std::cout << "Vector from C-style array:\n";
    std::copy(std::begin(vec_from_c_arr), std::end(vec_from_c_arr), std::ostream_iterator<char>{ std::cout });
    std::cout << '\n';

    // 5. Read the numbers from standard input and store them in the vector. Zero terminates the input.
    //    5.1. If the last number is 1, remove all numbers that are divisible by 2.
    //    5.2. If the last number is 2, insert three 1s after each number that is divisible by 3.
    vec.clear();
    int digit;
    std::cout << "\nEnter numbers:\n";
    while(std::cin >> digit && digit != 0) {
        vec.push_back(digit);
    }

    if(!vec.empty()) {
        if(const auto last_number{ vec.back() }; last_number == 1) {
            // Remove numbers divisible by 2
            for(auto it{ vec.begin() }; it != vec.end();)
                if(*it % 2 == 0) {
                    it = vec.erase(it);
                } else {
                    ++it;
                }
        } else if(last_number == 2) {
            // Insert three 1s after each number divisible by 3
            for(auto it{ vec.begin() }; it != vec.end();)
                if(*it % 3 == 0) {
                    it = vec.insert(it + 1, { 1, 1, 1 });
                    it += 3;
                } else {
                    ++it;
                }
        }
    }
    std::copy(std::begin(vec), std::end(vec), std::ostream_iterator<int>{ std::cout, " " });
    std::cout << '\n';

    // 6. Write a `void fillRandom(double* array, int size)` function that fills the array with random values in the
    //    range from -1.0 to 1.0. Fill the vectors of size 5, 10, 25, 50, 100 and sort the contents (using any of the
    //    developed algorithms adjusted for sorting real numbers).
    std::vector<double> random_vector;
    for(const auto count : { 5, 10, 25, 50, 100 }) {
        random_vector.resize(count);
        tasks::fill_random(random_vector.data(), random_vector.size());
        std::cout << "\nRandom filled vector of size " << count << " before sorting: [ ";
        std::copy(std::begin(random_vector), std::end(random_vector), std::ostream_iterator<double>{ std::cout, " " });

        tasks::insort_iter(random_vector.begin(), random_vector.end());
        std::cout << "]\nSorted vector: [ ";
        std::copy(std::begin(random_vector), std::end(random_vector), std::ostream_iterator<double>{ std::cout, " " });
        std::cout << "]\n";
    }
}
