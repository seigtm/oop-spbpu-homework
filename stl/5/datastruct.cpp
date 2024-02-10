// Baranov Konstantin Pavlovich, group v5130904/20021.
// STL. Lab #5.

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace setm {

struct DataStruct {
    int key1;
    int key2;
    std::string str;
};

std::ostream& operator<<(std::ostream& os, const DataStruct& datastruct) {
    os << "ds: [ key1: " << datastruct.key1
       << ",\tkey2: " << datastruct.key2
       << ",\tstr: \"" << datastruct.str << "\" ]";
    return os;
}

static int generate_key() {
    static std::default_random_engine gen{ std::random_device{}() };
    static std::uniform_int_distribution dist{ -5, 5 };

    return dist(gen);
}

static std::string generate_string() {
    static constexpr std::array strings{
        "Lorem ipsum", "dolor sit amet", "consectetur adipiscing",
        "elit", "sed do eiusmod", "tempor incididunt", "ut labore et",
        "dolore magna aliqua", "Ut enim ad", "minim veniam"
    };
    static std::default_random_engine gen{ std::random_device{}() };
    static std::uniform_int_distribution dist{ 0, static_cast<int>(strings.size() - 1) };

    return strings[dist(gen)];
}

void fill_random(std::vector<DataStruct>& datastructs, std::size_t count) {
    std::generate_n(std::back_inserter(datastructs), count, [] {
        return DataStruct{ generate_key(), generate_key(), generate_string() };
    });
}

}  // namespace setm


int main() {
    std::vector<setm::DataStruct> datastructs;
    setm::fill_random(datastructs, 10);

    std::cout << "Before sorting:\n";
    for(const auto& datastruct : datastructs) {
        std::cout << datastruct << '\n';
    }

    std::sort(datastructs.begin(), datastructs.end(), [](const auto& a, const auto& b) {
        if(a.key1 != b.key1)
            return a.key1 < b.key1;
        else if(a.key2 != b.key2)
            return a.key2 < b.key2;
        else
            return a.str.size() < b.str.size();
    });

    std::cout << "\nAfter sorting:\n";
    for(const auto& datastruct : datastructs) {
        std::cout << datastruct << '\n';
    }
}
