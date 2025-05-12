# Libft

Libft is a custom C library that reimplements a set of standard C library functions, along with additional utility functions and data structure operations. 

This is the first project in the common core of Hive and serves as the foundation for working with memory management, strings, and abstract data types in C. All code adheres to the strict 42 Network coding standard (*The Norm*). 

This library will be used in later projects, such as `printf`, `get_next_line`, and more, providing essential functionality for more advanced tasks.

## Project Goals

- Reimplement core functions from the C standard library
- Deepen understanding of memory management, pointers, and string handling
- Learn to build, organize, and maintain a personal utility library in C
- Practice implementing and manipulating linked lists
- Write clean, maintainable code under strict project constraints

## What’s Included

### **String Manipulation**

- `ft_strlen` – Returns the length of a string
- `ft_strlcpy` – Copies a string with size limitation
- `ft_strlcat` – Concatenates two strings with size limitation
- `ft_strchr` – Finds the first occurrence of a character in a string
- `ft_strrchr` – Finds the last occurrence of a character in a string
- `ft_strncmp` – Compares two strings up to a specified number of characters
- `ft_strdup` – Duplicates a string
- `ft_substr` – Extracts a substring from a string
- `ft_strjoin` – Joins two strings into a new string
- `ft_strtrim` – Trims characters from the start and end of a string
- `ft_split` – Splits a string into an array of strings
- `ft_itoa` – Converts an integer to a string
- `ft_strmapi` – Applies a function to each character of a string and returns a new string
- `ft_striteri` – Applies a function to each character of a string (in-place)

### **Memory Management**

- `ft_memset` – Sets a block of memory to a specified value
- `ft_bzero` – Clears a block of memory
- `ft_memcpy` – Copies a block of memory
- `ft_memmove` – Moves a block of memory
- `ft_memchr` – Searches for a character in a memory block
- `ft_memcmp` – Compares two memory blocks
- `ft_calloc` – Allocates memory and initializes it to zero
- `ft_atoi` – Converts a string to an integer
- `ft_isalpha` – Checks if a character is alphabetic
- `ft_isdigit` – Checks if a character is a digit
- `ft_isalnum` – Checks if a character is alphanumeric
- `ft_isascii` – Checks if a character is an ASCII character
- `ft_isprint` – Checks if a character is printable
- `ft_toupper` – Converts a character to uppercase
- `ft_tolower` – Converts a character to lowercase

### **File I/O**

- `ft_putchar_fd` – Writes a character to a file descriptor
- `ft_putstr_fd` – Writes a string to a file descriptor
- `ft_putendl_fd` – Writes a string followed by a newline to a file descriptor
- `ft_putnbr_fd` – Writes an integer to a file descriptor

### **Linked Lists**

- `ft_lstnew` – Creates a new linked list node
- `ft_lstadd_front` – Adds a node to the front of the list
- `ft_lstadd_back` – Adds a node to the back of the list
- `ft_lstdelone` – Deletes a node and frees its content
- `ft_lstclear` – Deletes and frees the entire list
- `ft_lstiter` – Applies a function to each element of the list
- `ft_lstmap` – Creates a new list by applying a function to each element
- `ft_lstlast` – Returns the last node of the list
- `ft_lstsize` – Returns the size (number of elements) of the list

## Compilation and Usage

### 1. Clone the Repository

Start by cloning the repository to your local machine:

```bash
git clone https://github.com/Waltsuuuu/Libft.git
cd libft
```

### 2. Compile the library

To compile the library, use the provided `Makefile`<br>
- `make` Compiles the library (*Does not include Linked List functions*)<br>
- `make bonus`Compiles the Linked List functions.

### 3. Clean and Rebuild

- `make clean` Removes the object files but keeps the library<br>
- `make fclean` Removes object files and the `libft.a` library<br>
- `make re` Cleans and then recompiles the entire project

### 4. Using Libft in your project

Include the header file `#include "Libft.h"` in your code<br><br>
When compiling your program, link the `libft.a` library using the `-L`and `-l`flags.<br>
Ex. `gcc main.c -L. -lft -o <progam_name>`


