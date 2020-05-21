# advent-of-code
Solutions to the coding challenges found at https://adventofcode.com/.

I am completing the 2019 Advent of Code and reading *Programming Principles and Practices Using C++* to familiarize myself with C++. I plan to eventually use C++ in some embedded projects.
***
## Running C++ code within Visual Studio Code (Notes)
1. Open Developer Command Prompt for VS 2017
2. Change to the directory of the current challange
3. Use `code .` to start Visual Studio Code instance
4. Follow [this guide](https://code.visualstudio.com/docs/cpp/config-msvc) to create build and debug scripts.
5. Use `ctrl+shift+b` to build the current file or `F5 ` to debug the current file.
6. Run the generated `solution.exe` to observe output.
***
## Comments on each day's challenge(s)
1. Getting used to C++ syntax. Nice to see a good use case for recursion (seems rare in practice).
2. I recently simulated a RISC computer in Register Transfer Notation for my Computer Architecture course at Ohio State. This problem is very similiar, so using good C++ practices was my mine focus.
3. I originally solved this problem with brute force, but the solution was slow. Implementing unordered sets in C++ is not trivial and I didn't want to develop a hash function for the line segments, so I calculated line segment intersections. Still think the logic could be cleaner somehow...
4. At first I tried to overcomplicate this because I was worried about the brute force issue I had with Day 3. Turns out you can just check every number's validity to solve this challenge, which is relatively easy.
5. Ran into many off-by-1 indexing errors here, but implemented the additional instructions. Learned that the `array[]` operator does not throw out of bounds exception, so `array.at()` must be used if you risk going out of array bounds.
6. C++ does not provide a tree datatype in the STL library, so I implemented a basic tree datatype with string and set datatypes. I would try the Boost library, but I want to complete these challenges with "pure" C++.
