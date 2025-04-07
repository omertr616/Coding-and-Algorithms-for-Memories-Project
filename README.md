# Coding and Algorithms for Memories Project

### SCS Algorithms

Algorithms to compute the SCS of several sequences when it is known
they all result from a length-n sequence with deletions. For example, assume there is a fixed
number of sequences all received by t deletions from some length-n sequence x. The goal is
to find their SCS with good complexity (better than the multiplication of their lengths).

https://www.overleaf.com/read/rtcccdmqgkpm#af0160

## Getting Started

 These instructions will guide you through setting up and running test cases for the algorithms presented in our project. Follow the steps below to run the tests locally on your machine.

### Prerequisites

Before running the project, make sure you have the following installed:

- **C++ Compiler** (g++, clang++, or MSVC)

- **Git** (to clone the repository)

- **Python 3.x installed** (recommended: Python 3.8+)

- **pip or pip3** (for installing Python packages)

- **`matplotlib` library** (install using pip, for plotting performance graphs)

### Installing
To set up the project on your local machine, follow these steps:

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/your-username/Coding-and-Algorithms-for-Memories-Project.git
   ```

2. Navigate into the project directory:
   ```bash
   cd Coding-and-Algorithms-for-Memories-Project
   ```

## Running the tests

In this section, we will explain how to run tests for each of the algorithms presented in the project and provide their respective meanings.

#### 1. <u>Dynamic Programming</u>  

We provide an example to compute the SCS of two strings:

`str1 = "abac"`  `str2 = "cab"`

To run this example using the DP algorithm, execute the following commands:
   ```
    g++ -o output_file regular_dynamic_programming.cpp
    output_file.exe 
   ```

#### 2.1 <u>Dynamic Programming with 0-1 BFS for 2 Sequences</u>

To compute the last example using the optimized DP algorithm with 0-1 BFS, run the following commands:
   ```
    g++ -o output_file SCS_two_sequences.cpp
    output_file.exe 
   ```

#### 2.2 <u>Dynamic Programming with 0-1 BFS for Three or More Sequences</u>
During the project, we observed that this algorithm does not handle all cases correctly. For example, given the input sequences {"AB", "BB", "BA"}, it produces the output "ABBA", which has a length of 4. However, the actual shortest common supersequence (SCS) has a length of 3, such as "BAB".

This test demonstrates how the algorithm produces different results for the same input sequences (using the specific example we discussed):

Input: {"AB", "BB", "BA"}  , Output: ABBA

Input: {"BB", "AB", "BA"}  , Output: BAB

Input: {"AB", "BA", "BB"}  , Output: ABAB 

Run the example using the following commands:

   ```
    g++ -o output_file bad_generalization_for_multiple_sequences.cpp
    output_file.exe 
   ```
   
#### 3. <u>Dynamic programming with 0-1 BFS for Multiple Sequences</u>

Run the tests with the commands:

   ```
    g++ -o output_file SCS_multiple_sequences.cpp
    output_file.exe 
   ```

## Authors

* Omer Trinin 
* Keren Mirzahi

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* **E.W. Myers**, *An O(ND) difference algorithm and its variations*, Algorithmica, 1:251–266, 1986.
* **R.W. Irving, C.B. Fraser**, *Two algorithms for the longest common subsequence of three (or more) strings*, In *Proceedings of the Annual Symposium on Combinatorial Pattern Matching*, Tucson, AZ, USA, 29 April–1 May 1992; pp. 214–229.

* **V.G. Timkovskii**, *Complexity of Common Subsequence and Supersequence Problems and Related Problems*

