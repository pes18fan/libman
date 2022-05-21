# libman

A simple library management terminal app written in C.

# Capabilities

- Add books to the list with an accession number, title, author and price information. This info is stored in a .dat file
- Display the book list on the console, pulling it from the .dat file
- Find a particular book(s) based on the author or the title based on the accession number
- List the book count in the list
- Display the book list arranged in ascending order based on the accession number

Supports upto 50 instances of book info storage; increase it by changing the array size for the library structure, i.e. change the `50` in line 21 (the line has the code `lib[50];`) to whatever number you wish and recompile.

# Special thanks

- [Neeraj319](https://github.com/Neeraj319) for fixing much of the code.
