// Baranov Konstantin Pavlovich, group v5130904/20021.
// STL. Lab #7.

#include <algorithm>
#include <format>
#include <iostream>
#include <limits>
#include <random>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

namespace setm {

class statistics {
public:
    // Functor operator to process each element in the sequence.
    void operator()(int value) {
        // Update maximum and minimum values.
        max = std::max(max, value);
        min = std::min(min, value);

        // Update counts for positive and negative numbers.
        if(value > 0)
            positives++;
        else if(value < 0)
            negatives++;

        // Update sum of odd and even numbers.
        if(value % 2)
            odd_sum += value;
        else
            even_sum += value;

        // If it's the first element, update `first` variable.
        if(count == 0)
            first = value;

        // Always update `last` variable and increment `count`.
        last = value;
        ++count;
    }

    std::string printStatistics() const {
        if(count == 0)
            return "Empty sequence";

        return std::format(
            "Number of elements: {}\n"
            "Maximum number: {}\n"
            "Minimum number: {}\n"
            "Average: {}\n"
            "Positive numbers: {}\n"
            "Negative numbers: {}\n"
            "Sum of odd numbers: {}\n"
            "Sum of even numbers: {}\n"
            "First and last element match: {}",
            count,
            max,
            min,
            static_cast<double>(odd_sum) / count + static_cast<double>(even_sum) / count,
            positives,
            negatives,
            odd_sum,
            even_sum,
            (first == last ? "Yes" : "No"));
    }

private:
    int max{ std::numeric_limits<int>::min() };
    int min{ std::numeric_limits<int>::max() };
    std::size_t positives{};
    std::size_t negatives{};
    int odd_sum{};
    int even_sum{};
    std::size_t count{};
    int first{};
    int last{};
};

}  // namespace setm

int main() {
    // Generate 30 random numbers in [-500, 500].
    static constexpr auto sequence_size{ 30 };
    static constexpr auto min_value{ -500 };
    static constexpr auto max_value{ 500 };
    std::vector<int> sequence(sequence_size);
    std::ranges::generate(sequence, [] {
        static std::default_random_engine gen{ std::random_device{}() };
        static std::uniform_int_distribution dist{ min_value, max_value };

        return dist(gen);
    });

    // Output the sequence.
    std::cout << "Generated sequence: { ";
    std::ranges::copy(sequence, std::ostream_iterator<int>{ std::cout, " " });
    std::cout << " }\n";

    // Process each element in the sequence and gain the statistics.
    setm::statistics stats;
    std::ranges::for_each(sequence, [&stats](auto value) { stats(value); });

    // Output the statistics.
    std::cout << "Statistics:\n"
              << stats.printStatistics() << '\n';
}
