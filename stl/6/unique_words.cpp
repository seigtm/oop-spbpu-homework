// Baranov Konstantin Pavlovich, group v5130904/20021.
// STL. Lab #6.1.

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_set>

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return EXIT_FAILURE;
    }

    std::ifstream file{ argv[1] };
    if(!file) {
        std::cerr << "Failed to open the file.\n";
        return EXIT_FAILURE;
    }

    // Read the entire content of the file into a string efficiently using stream iterators.
    std::string text{ std::istreambuf_iterator<char>{ file }, {} };

    // Close the file explicitly after reading its content.
    // It's not necessary because ifstream destructor
    // will close the file automatically, but it's good practice.
    file.close();

    // Convert all alphabetic characters in the string to lowercase while
    // replacing non-alphabetic characters with spaces.
    std::transform(text.begin(), text.end(), text.begin(), [](char c) {
        return std::isalpha(c) ? std::tolower(c) : ' ';
    });

    // Use stringstream to tokenize the transformed text and store unique words in an unordered_set.
    std::stringstream ss{ text };
    std::unordered_set<std::string> unique_words{ std::istream_iterator<std::string>{ ss },
                                                  std::istream_iterator<std::string>{} };

    // Output the unique words.
    for(const auto& word : unique_words)
        std::cout << word << '\n';

    // Output the total number of unique words found.
    std::cout << "There are " << unique_words.size() << " unique words.\n";
}
