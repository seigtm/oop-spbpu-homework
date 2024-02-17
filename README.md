# Object-Oriented Programming Labs Repository

This repository contains laboratory assignments related to the course "Object-Oriented Programming" taught at Saint Petersburg Polytechnic University.

## Repository Structure

The `./stl` directory contains labs related to learning C++ Standard Template Library (STL) algorithms and concepts.

The `./mfc` directory contains labs focused on Microsoft Foundation Class Library (MFC), which is a C++ object-oriented library for Windows desktop application development.

## Getting Started

To get started with the labs in this repository, follow these steps:

1. Clone the repository to your local machine.
2. Navigate to the specific lab directory (e.g., `./stl/8/`).
3. Explore the source code.

## Contributing

Contributions to this repository are welcome! If you have suggestions for improvements or would like to add your
own lab assignments, feel free to submit a pull request.

## STL Labs Overview

### Lab 1: Vector

- **Task Description**:
  - Implement sorting algorithms for a vector of integers using different access methods.
  - Read data from a text file into a vector.
  - Read numbers from standard input, modify vector based on input, and print the result.
  - Fill vectors with random values and sort them.

- **Implementation**:
  - **Sorting Algorithms**:
    - **Using `operator[]`** (`insort_brackets` function): Implements insertion sort algorithm using the `operator[]` for access.
    - **Using `at()` Method** (`insort_at` function): Implements insertion sort algorithm using the `at()` method for access.
    - **Using Iterators Only** (`insort_iter` function): Implements insertion sort algorithm using only iterators for access, without using any other operations besides getting the current element and advancing to the next one.
  - **Reading from Text File**:
    - Reads the contents of a text file into a C-style array and copies the data into a vector without using loops or STL algorithms.
  - **Processing Standard Input**:
    - Reads numbers from standard input and stores them in a vector. If the last number is 1, removes all numbers divisible by 2. If the last number is 2, inserts three 1s after each number divisible by 3.
  - **Filling Vectors with Random Values**:
    - Implements a function `fillRandom` to fill an array with random values in the range from -1.0 to 1.0. Uses this function to fill vectors of various sizes (5, 10, 25, 50, 100) with random values and sorts the contents using one of the sorting algorithms implemented earlier, adjusted for sorting real numbers.

- **Source Code**:
  - The source code demonstrates the implementation of various vector manipulation tasks, including sorting, reading from file, processing standard input, and filling with random values.
  - It uses algorithms such as insertion sort and iterators to perform sorting operations efficiently.
  - The code efficiently handles input/output operations, demonstrating understanding of vector manipulation and standard library functionalities.

### Lab 2: Strings

- **Task Description**:
  1. Read the content of a text file, which may contain:
     - Words composed of Latin lowercase and uppercase letters, as well as digits, with a maximum length of 20 characters.
     - Punctuation marks: ".", ",", "!", "?", ":", ";".
     - Whitespace characters: space, tab, newline.
  2. Format the text as follows:
     - Remove whitespace characters other than space.
     - Do not allow more than one consecutive space.
     - Do not place a space between a word and a punctuation mark.
     - Always place a space after a punctuation mark.
     - Replace words longer than 10 characters with "Vau!!!".
  3. Convert the formatted text into a set of lines, each containing a whole number of words and not exceeding 40 characters in length.

- **Implementation**:
  - **Text Formatting Functions**:
    - `remove_whitespaces`: Removes whitespace characters other than space.
    - `remove_consecutive_whitespaces`: Removes consecutive whitespace characters.
    - `insert_space_after_punctuation`: Inserts a space after each punctuation mark.
    - `remove_space_before_punctuation`: Removes space before punctuation marks.
    - `replace_long_words`: Replaces words longer than 10 characters with "Vau!!!".
    - `transform_into_lines`: Converts the formatted text into a set of lines not exceeding 40 characters in length.
  - **Main Functionality**:
    - Reads text from a file and applies formatting functions to it.
    - Converts the formatted text into a set of lines and ensures that each line does not exceed 40 characters in length.

- **Source Code**:
  - The source code effectively implements the required text formatting tasks using various string manipulation techniques.
  - It demonstrates understanding of string processing, including removal of whitespace characters, insertion/removal of spaces around punctuation marks, and replacement of long words.
  - The code efficiently handles input/output operations and correctly formats the text as per the specified requirements.

### Lab 3: List & Deque

#### Task 1: Priority Queue Implementation

- **Description**:
  - Implemented a priority queue class with three priority levels: low, normal, and high.
  - Elements are added to the queue with a specified priority and extracted based on their priority level and insertion order.
  - Acceleration operation increases the priority of low priority elements to high, causing them to bypass normal priority elements.
- **Implementation**:
  - Utilized `std::list` to store elements with each priority level represented by a separate list.
  - Implemented methods for adding elements with a given priority, extracting the top priority element, and accelerating low priority elements.
  - The class efficiently manages elements according to their priority levels and ensures correct extraction order.
- **Testing**:
  - Created a priority queue instance and tested various scenarios by adding elements with different priorities and performing acceleration.
  - Checked the correctness of the queue operations using debug output, demonstrating the proper functioning of the class.

#### Task 2: Zigzag List Output

- **Description**:
  - Developed a program to fill a list of integers with random values and output its elements in a zigzag order.
  - Zigzag order involves printing the first, last, second, second to last, and so on elements of the list.
- **Implementation**:
  - Utilized `std::list` to store random integer values.
  - Implemented the zigzag output by iterating through the list with two iterators, one starting from the beginning and the other from the end.
  - Handled odd-sized lists by printing the middle element only once.
- **Testing**:
  - Tested the program with lists of various sizes (0, 1, 2, 3, 4, 5, 7, 14) to ensure correct behavior in different scenarios.
  - Verified the zigzag output by comparing it with the expected output for each list size.

### Lab 4: Iterators

- **Description**:
  - Implemented a container class that stores factorial values from 1! to 10!.
  - Implemented an iterator class for enumerating elements of this container.
  - Access to the elements of this container is possible only through iterators returned by `begin()` and `end()` functions.
  - The container does not store its elements in memory; they are computed when accessed through iterators.
- **Implementation**:
  - Created `factorial_container` class with default constructor and functions `begin()` and `end()` returning iterators.
  - Implemented `factorial_iterator` class as a bidirectional iterator for enumerating factorial values.
  - Overloaded operators `*`, `++`, `--`, `==`, and `!=` for the iterator to enable iteration and comparison.
- **Compatibility**:
  - Ensured compatibility with the STL by testing with algorithms like `copy` to copy container contents into a `std::vector<int>`.
  - Verified compatibility by successfully copying the contents of the custom container into a `std::vector<int>` using the `copy` algorithm.

### Lab 5: Algorithms

- **Description**:
  - Developed a program that performs the following actions:
    1. Fills a vector of `DataStruct` structures with random values:
       - `key1` and `key2` are generated randomly in the range from -5 to 5.
       - `str` is filled from a table of 10 arbitrary strings, and the index of the string is generated randomly.
    2. Prints the filled vector.
    3. Sorts the vector in the following order:
       1. Ascending order of `key1`.
       2. If `key1` values are equal, sorts in ascending order of `key2`.
       3. If both `key1` and `key2` values are equal, sorts in ascending order of the length of `str`.
    4. Prints the sorted vector.
- **Implementation**:
  - Defined a `DataStruct` structure with `key1`, `key2`, and `str` members.
  - Implemented a `fill_random` function to populate the vector with random `DataStruct` objects.
  - Utilized a lambda function as the sorting predicate in `std::sort` to define the custom sorting order based on `key1`, `key2`, and the length of `str`.
- **Execution**:
  - Generated 10 random `DataStruct` objects and printed them before sorting.
  - Sorted the vector based on the specified criteria.
  - Printed the sorted vector to demonstrate the sorting result.

### Lab 6: Algorithms 2

#### Task 1: Reading and Tokenizing Text File

- **Description**:
  - Developed a program that performs the following actions:
    1. Reads the content of a text file.
    2. Tokenizes the text into words, considering a word as a sequence of characters separated by spaces, tabs, and/or newline characters.
    3. Outputs the list of unique words present in the text without repetitions.
- **Implementation**:
  - Utilized standard algorithms and data structures such as `std::unordered_set` and `std::transform`.
  - Tokenized the text using `std::stringstream` and `std::istream_iterator`.
- **Execution**:
  - Provided a command-line argument specifying the input file.
  - Read the content of the file, tokenized it, and outputted the unique words found.

#### Task 2: Manipulating Vector of Geometric Shapes

- **Description**:
  - Developed a program that performs various operations on a vector of geometric shapes:
    1. Fills the vector with randomly generated geometric shapes such as triangles, squares, rectangles, and pentagons.
    2. Counts the total number of vertices of all shapes in the vector.
    3. Counts the number of triangles, squares, rectangles, and pentagons in the vector.
    4. Removes all pentagons from the vector.
    5. Creates a new vector containing the coordinates of one vertex of each shape.
    6. Reorders the shapes in the vector so that triangles come first, followed by squares, then rectangles, and finally pentagons.
  - Utilized standard algorithms like `std::generate_n`, `std::accumulate`, `std::count_if`, `std::remove_if`, `std::transform`, and `std::stable_partition`.
- **Implementation**:
  - Defined structures for points and shapes and overloaded the necessary operators for printing.
  - Implemented functions for generating random shapes, counting vertices, counting shapes, removing shapes, extracting vertices, and reordering shapes.
- **Execution**:
  - Generated random shapes and added additional squares for testing purposes.
  - Performed various operations on the vector of shapes and printed the results at each step to demonstrate the changes made.

### Lab 7: Functors

#### Task: Functor for Collecting Statistics

- **Description**:
  - Developed a functor that collects statistics about a sequence of integers.
  - After processing the sequence with the `for_each` algorithm, the functor provides the following statistics:
    1. Maximum number in the sequence
    2. Minimum number in the sequence
    3. Average number in the sequence
    4. Number of positive numbers
    5. Number of negative numbers
    6. Sum of odd elements in the sequence
    7. Sum of even elements in the sequence
    8. Whether the first and last elements of the sequence match.
  - Tested the program on randomly generated sequences.
- **Implementation**:
  - Defined a functor class `statistics` with overloaded `operator()` to process each element in the sequence.
  - Implemented methods to update maximum and minimum values, count positive and negative numbers, calculate the sum of odd and even numbers, and check the first and last elements of the sequence.
  - Provided a method `printStatistics()` to print the collected statistics.
- **Execution**:
  - Generated a sequence of 30 random numbers in the range [-500, 500].
  - Processed each element in the sequence using the functor to collect statistics.
  - Printed the generated sequence and the collected statistics.

### Lab 8: Functors 2

#### Task 1: Multiplying Numbers by PI

- **Description**:
  - Developed a program that multiplies each element in a list of floating-point numbers by the value of PI using only standard algorithms and functors.
  - Tested the program on randomly generated sequences of numbers.
- **Implementation**:
  - Defined a functor `multiply_by_pi` that multiplies a number by PI.
  - Generated a sequence of random floating-point numbers.
  - Applied the functor to each element in the sequence using the `transform` algorithm.
- **Execution**:
  - Generated a sequence of random numbers in the range [0.0, 5.0].
  - Multiplied each number by PI using the defined functor.
  - Printed the original numbers and the resulting numbers after multiplication by PI.

#### Task 2: Geometric Shapes Hierarchy and Sorting

- **Description**:
  - Developed a program that implements an inheritance hierarchy of geometric shapes, including `Circle`, `Triangle`, and `Square` classes derived from the base class `Shape`.
  - The `Shape` class contains information about the position of the center of the shape, methods to determine if a shape is more left or upper than another shape, and a pure virtual function `draw`.
  - The program maintains a list of shape pointers and performs various operations using standard algorithms and adapters.
- **Implementation**:
  - Defined the base class `Shape` and derived classes `Circle`, `Triangle`, and `Square`.
  - Implemented methods to draw each shape and determine their position relative to other shapes.
  - Generated random shapes and populated a list with pointers to these shapes.
  - Used standard algorithms and adapters to draw the shapes, sort them based on different criteria, and then draw them again.
- **Execution**:
  - Generated a list of random shapes.
  - Drew all shapes and then sorted and drew them based on their position from left to right, right to left, top to bottom, and bottom to top.

## MFC Labs Overview

I won't provide the logic for these labs as they are essentially step-by-step exercises from the teacher's manual.

However, I have made some bug fixes along the way. Below, I will list each lab title along with its corresponding path in the repository.

All laboratory assignments are compiled using a single Visual Studio Solution file: [`./mfc/mfc.sln`](https://github.com/seigtm/oop-spbpu-homework/tree/master/mfc/mfc.sln).

### Lab 1: Your First Visual C++ Application

**Path**: [`./mfc/1/Hello/`](https://github.com/seigtm/oop-spbpu-homework/tree/master/mfc/1/Hello)

### Lab 2: Controls, Properties, and Events

**Path**: [`./mfc/2/Test/`](https://github.com/seigtm/oop-spbpu-homework/tree/master/mfc/2/Test)

### Lab 3: Working with the Mouse

**Path**: [`./mfc/3/Draw/`](https://github.com/seigtm/oop-spbpu-homework/tree/master/mfc/3/Draw)

### Lab 4: Working with the Keyboard

**Path**: [`./mfc/4/MyKey/`](https://github.com/seigtm/oop-spbpu-homework/tree/master/mfc/4/MyKey)

### Lab 5: Working with Menus

**Path**: [`./mfc/5/Speed/`](https://github.com/seigtm/oop-spbpu-homework/tree/master/mfc/5/Speed)

### Lab 6: Predefined Dialog Boxes

**Path**: [`./mfc/6/MyMsg/`](https://github.com/seigtm/oop-spbpu-homework/tree/master/mfc/6/MyMsg)

### Lab 7: Drawing Shapes

**Path**: [`./mfc/7/Graph/`](https://github.com/seigtm/oop-spbpu-homework/tree/master/mfc/7/Graph)

### Lab 8: Graphics Editor

**Path**: [`./mfc/8/PaintORama/`](https://github.com/seigtm/oop-spbpu-homework/tree/master/mfc/8/PaintORama)

### Lab 9: "Deal Cards" Game

**Path**: [`./mfc/9/FourUp/`](https://github.com/seigtm/oop-spbpu-homework/tree/master/mfc/9/FourUp)

### Lab 10: Opening BMP Files

**Path**: [`./mfc/10/BmpOpen/`](https://github.com/seigtm/oop-spbpu-homework/tree/master/mfc/10/BmpOpen)

### Lab 11: Running the Program in the Background

**Path**: [`./mfc/11/Tasks/`](https://github.com/seigtm/oop-spbpu-homework/tree/master/mfc/11/Tasks)
