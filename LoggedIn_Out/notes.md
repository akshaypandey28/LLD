- The Precision Engine (<chrono>): We used this modern C++ library to interact directly with the 
computer's hardware clock for exact timing.


- The Timestamp (system_clock::time_point): This is the specific variable type we used to freeze 
and store the exact microsecond an action happened.


- The Raw Data (time_t): This is the underlying format—a large integer that simply counts the 
number of seconds that have passed since January 1, 1970.


- The Advantage of time_t: Because it is just a count of seconds, it makes it incredibly easy for 
the system to do math (like calculating total session duration).


- The Translator (<ctime>): We used this legacy C library to translate the raw hardware ticks 
into a format humans can actually read.


- The Output (ctime()): This specific function formats the time_t integer into legible text, 
allowing us to print strings like "Sat Apr 4 17:40:00 2026" to the screen.


- ctime() function automatically adds a hidden newline character (\n) to the very end of the text string it creates.

`to_time_t()`
- The Input: It takes a std::chrono::system_clock::time_point (the modern way C++ tracks time).

- The Process: It calculates how many seconds have passed since the Unix Epoch (January 1, 1970).

- The Output: It returns a std::time_t value. This is a simple integer type (usually a long or long long).

`using namespace std::chrono;`
- In C++, a namespace is like a folder that organizes related code to prevent naming conflicts.

- std stands for the "standard" library, which is the main folder for all built-in C++ tools.

- chrono is a sub-folder inside std specifically dedicated to precise time and clocks.

- When we write using namespace std::chrono;, we are bringing all the tools from that 
sub-folder into our current workspace.

- This saves us from having to type the full, long path every time we want to use a time function.

- Without this line, we should have to type the full name: std::chrono::system_clock::now();

- With this line, we can write the much shorter version: system_clock::now();