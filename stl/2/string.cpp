// Baranov Konstantin Pavlovich, group v5130904/20021.
// STL. Lab #2.

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Markov algorithm rules:
// 1. ['\t', '\n'] -> ' '
// 2. ' '{2+} -> ' '
// 3. [A-Za-z0-9]' '['.', ',', '!', '?', ':', ';'] ->[A-Za-z0-9]['.', ',', '!', '?', ':', ';']
// 4. ['.', ',', '!', '?', ':', ';'] -> ['.', ',', '!', '?', ':', ';']' '
// 5. [A-Za-z0-9]{11+} -> "Vau!!!"

namespace setm {

namespace constants {
constexpr std::size_t MAX_WORD_LENGTH{ 10 };
constexpr std::size_t MAX_LINE_LENGTH{ 40 };
}  // namespace constants

// Remove whitespaces except spaces.
void remove_whitespaces(std::string& text) {
    text.erase(std::remove_if(text.begin(), text.end(), [](char c) {
                   return c == '\t' || c == '\n';
               }),
               text.end());
}


// Remove consecutive whitespaces.
void remove_consecutive_whitespaces(std::string& text) {
    text.erase(std::unique(text.begin(), text.end(), [](char a, char b) {
                   return std::isspace(a) && std::isspace(b);
               }),
               text.end());
}

// Insert space after each punctuation symbol.
void insert_space_after_punctuation(std::string& text) {
    const std::string punctuation{ ".,!?:;" };
    for(char punc : punctuation) {
        auto found{ text.find_first_of(punc) };
        while(found != std::string::npos) {
            text.insert(found + 1, " ");
            found = text.find_first_of(punctuation, found + 2);
        }
    }
}

// Remove space between word and punctuation symbol.
void remove_space_before_punctuation(std::string& text) {
    const std::string punctuation{ ".,!?:;" };
    std::size_t found{};
    while((found = text.find_first_of(punctuation, found)) != std::string::npos) {
        if(found > 0 && text[found - 1] == ' ') {
            text.erase(found - 1, 1);
        }
        ++found;
    }
}

// Replace words longer than 10 characters with "Vau!!!".
void replace_long_words(std::string& text) {
    std::istringstream iss{ text };
    std::ostringstream oss;
    std::string word;
    while(iss >> word) {
        if(word.size() > constants::MAX_WORD_LENGTH) {
            oss << "Vau!!!";
            // If the word ends with a punctuation symbol, we should preserve it.
            if(const auto word_last_char{ word.back() }; std::ispunct(word_last_char))
                oss << word_last_char;
        } else {
            oss << word;
        }
        oss << ' ';
    }

    text = oss.str();
}

// Transform the result text into a collection of lines with no more than 40 characters.
std::vector<std::string> transform_into_lines(const std::string& text) {
    std::istringstream iss{ text };
    std::vector<std::string> lines;
    std::string line;
    std::string word;
    std::size_t line_length{};

    while(iss >> word) {
        // Check if adding the word exceeds the maximum line length:
        if(line_length + word.size() + 1 > constants::MAX_LINE_LENGTH) {
            lines.emplace_back(line);       // Push the current line into the vector.
            line = word + ' ';              // Start a new line with the current word.
            line_length = word.size() + 1;  // Update line length.
        } else {
            line += word + ' ';              // Add word to the current line.
            line_length += word.size() + 1;  // Update line length.
        }
    }

    if(!line.empty())
        lines.emplace_back(line);  // Push the last line into the vector if it's not empty.

    return lines;
}

}  // namespace setm

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
    std::string text{ std::istreambuf_iterator<char>(file), {} };

    setm::remove_whitespaces(text);
    setm::remove_consecutive_whitespaces(text);
    setm::insert_space_after_punctuation(text);
    setm::remove_space_before_punctuation(text);
    setm::replace_long_words(text);
    const std::vector lines{ setm::transform_into_lines(text) };
    for(const auto& line : lines) {
        assert(line.length() <= setm::constants::MAX_LINE_LENGTH);
        std::cout << line << '\n';
    }
}
