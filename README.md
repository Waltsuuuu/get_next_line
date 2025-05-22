# get_next_line

`get_next_line` is a function written in C that reads a file or standard input one line at a time. It returns a freshly allocated string containing the next line each time it's called, including the newline character (`\n`) if present. 

---

This repository contains two versions of the `get_next_line()` function.

**v.1 "Mandatory"** 
(get_next_line.c, get_next_line.h, get_next_line_utils.c)
- - Designed to handle one FD at a time, until EOF.

**v.2 "Bonus"** (get_next_line_bonus.c, get_next_line_bonus.h, get_next_line_utils_bonus.c)
- - Designed to handle multiple file descriptors with alternating read calls to each, without losing state.

---

**Features**

- **Works with any file size**, regardless of newline placement
- **Preserves leftover data** between calls
- **Handles files without a trailing newline** (returns the last line properly)
- **No memory leaks**, even if the function isn’t called until EOF
- **Efficient buffer usage** via `BUFFER_SIZE` (read in chunks)
- **EOF handling** – returns `NULL`
- **Safe dynamic memory management** using `malloc`, `free`, and custom helper functions
- **Clean separation of logic**: reading, line extraction, memory management
- **Compatible with standard file descriptors** (`stdin`, files, pipes, etc.)


**Bonus Version Features**

- **Supports multiple file descriptors** simultaneously
- **Per-FD state management** via a linked list of nodes
- **Automatically frees and unlinks** each FD node when its stream reaches EOF
- **Interleaved FD calls** work correctly (you can alternate reads on different FDs)
- **Independent leftover buffers** for each FD, preventing cross-contamination of data  

***Note...***

- The use of `lseek()` and global variables was forbidden for this project.

---

<details>

<summary>Example usage</summary>
<br>
Reads the file `example.txt` line by line, prints each line to the terminal, and properly frees memory after each line.

```c
int fd = open("example.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

</details>

---

## Mandatory (v.1)
The first version of this function is designed to work with only one file descriptor at a time.
It uses a single static character array to store leftover data between calls.
As a result, the function must be called repeatedly until it reaches EOF before switching to a new file descriptor.

<details>

<summary> Concise breakdown </summary>
<br>

1. **Static Initialization**

On the first call, the static leftover buffer is empty. On subsequent calls, it contains any data that was read after the last newline.

2. **Allocate Temporary Buffer**

A temporary buffer `buf` of size `BUFFER_SIZE + 1` is allocated to hold the output of the read() system call.

3. **Initialize stash**

The contents of `leftover` (if any) are duplicated into a new `stash` string, which will accumulate data for the current line.

4. **Read Until Newline or EOF**

The `read_operation()` function reads repeatedly from `fd`, appending each read chunk from `buf` to `stash`, until:

- A newline character is found in `stash`, or `read()` returns 0 (EOF) or -1 (error).

5. **Check for End of Data**

If `stash` ends up empty (no data read), the function:

- Frees `buf` and `stash`
- Returns NULL to indicate no more lines.

6. **Extract the Line**

The `extract_line()` function:

- Copies characters from `stash` up to and including the first newline into `line`

- Copies any remaining characters after the newline into `leftover`, to be used in the next call.

7. **Clean Up and Return**

- Frees `buf` and `stash`

- Returns the `line` just extracted.


</details>

<details>
<summary>Line by line breakdown</summary>

### 1. Variables
`char *buf`

- Temporary buffer to hold data read from the file descriptor during each `read()` call.
<br>

`char *stash`

- Dynamically growing string that holds all data read so far in the current `gnl` call.
- - After each `read()` call, the contents read into `buf` are appended to `stash`.
<br>

`char *line`

- Pointer to the line that will be returned. Up to and containing the newline or end of file.
<br>

`static char leftover[BUFFER_SIZE + 1];`

- Stores any remaining characters _after_ the newline in the peviously returned line.
- - Declared as `static` so it persists across multiple calls, but is local to the function.
- - Declared as a fixed-size static array to avoid dynamic memory allocation for leftover data. This ensures that if the program ends before get_next_line() is called until EOF, no memory leak occurs from leftover data.

---
### 2. Initialize
```c
buf = malloc(BUFFER_SIZE + 1);
```
Dynamically allocates memory for the temporary buffer `buf` using `malloc()`.

- This buffer is used in the subsequent `read()` calls to temporarily hold chunks of data before appending the data to `stash`.

- `BUFFER_SIZE` is a predetermined constant that determines how many bytes to read at a time. It is defined in `get_next_line.h` and set to 32 bytes. This can also be adjusted by compiling the program using the define flag `-D`. 

- - `cc main.c -D BUFFER_SIZE=9999.`

- The `+1` is to allocate space for a null termintor, so the buffer can be treated as a valid string after reading.
<br>

```c
stash = ft_strdup(leftover);
````
This duplicates the contents of the static `leftover` array and returns a dynamically allocated string. 

This is essential for preserving line continuity across multiple `read()` calls.

- On the first call, `leftover` is a zero-initialized static array _(i.e an empty string)_, so `stash` begings as an empty string _("")_.
- On subsequent `gnl` calls, `leftover` may contain leftover characters from the last read call _(everything after the last newline)_.
- `stash` becomes the starting point for accumulating the full line. Any new data `read()` from the file will be appended to it. 

---

### 3. Read and Accumulate data

```c
stash = read_operation(fd, buf, stash);
```
Calls the helper function `read_operation()` to read `BUFFER_SIZE`chunks of data from the file descriptor `fd`, into `buf` and append it to the `stash`.

After each `read()`, the `stash` is checked to see if it contains a newline `\n` character OR  if `read()` returned 0 or -1, indicating end of the file (EOF) or a read error.
- If a newline character is found, the current `stash` is returned.
- If EOF / error, the `stash` _(which may contain partial data)_ is retuned.

---

<details>

<summary> Helper function read_operation() line by line breakdown </summary>
<br>

**Function prototype**

`char	*read_operation(int fd, char *buf, char *stash)`
- `fd` The file descriptor to read from
- `buf` A temporary buffer to store data read from `fd`
- `stash` A dynamically allocated string to hold accumulated data so far


**Variables**

`int bytes_read;`
- Number of bytes read by the latest `read()` call.

`char *temp_stash*`
- Temporary pointer used to store the result of appending `buf` to `stash`, before assigning the resulyt back to `stash`. Prevents memory leaks when updating `stash`.

**Logic** 

```c
if (ft_strchr(stash, '\n'))
    return (stash);
```
Checks if the current `stash` already contains a newline character.
- If true, returns `stash` immdediately without reading more, because we already have at least one full line in `stash`.
<br>

```c
while (1)
{
```
Starts an infinite loop to read data chunks until a newline character is found OR EOF/error occurs.
<br>
<br>

```c
    bytes_read = read(fd, buf, BUFFER_SIZE);
```
Reads up to `BUFFER_SIZE` bytes fom `fd` into `buf`.

`bytes_read` will be:
- \> 0: Number of bytes read.
- == 0: End of file (EOF).
- < 0: read error.
<br>

```c
	if (bytes_read <= 0)
		buf[0] = '\0';
	else
		buf[bytes_read] = '\0';
```
- If nothing read (EOF or error), set `buf` to an empty string.
- Otherwise, null-terminate `buf` after the bytes, turning `buf` into a valid C-string.
<br>

```c
    temp_stash = ft_strjoin(stash, buf);
    free(stash);
    stash = temp_stash;
````
- `temp_stash` stores the result of `ft_strjoin`, which allocates a new block of memory and copies both `stash` and `buf`into it.
- Since `stash` points to a previously allocated string, `free()` the old `stash`to avoid memory leaks.
- Update `stash` to point to the newly allocated concatenated string.
<br>

```c
    if (ft_strchr(stash, '\n') != NULL || bytes_read <= 0)
        break ;
```
Checks if the updated `stash` now contains a newline character or if EOF / error was eached _(bytes_read <= 0)_
- If either condition is true, exit the loop because we either have a complete line or no more data.
<br>

```c
}
return (stash);
```
Finally return `stash` which **contains all accuulated data up to (and possibly including) a newline, or all data read until EOF / error.**

Exit function.

</details>

---

### 4. End of file / Error check.
```c
if (stash == NULL || *stash == '\0')
```
This block ensures we don't process empty or invalid data.

- `stash == NULL` Memory allocation failed in either `ft_strdup()` or `ft_strjoin()` OR EOF was reached before any data was read.
- `*stash == '\0'` Stash is an empty string, meaning there is nothing to return.
<br>

```c
{
	free (buf);
	free (stash);
	stash = NULL;
	return (NULL);
}
```
If true;
- Free the temporary buffer `buf` that was allocated for reading data.
- Free the dynamically allocated `stash` string.
- Then also set `stash` to NULL, since `free()` does not set `stash` to NULL. It just deallocates the memory, leaving `stash` as a dangling pointer, meaning it still contains the same memory address, which now points to freed (invalid) memory.
- Finally return (NULL). This signals to the caller that EOF was reached and there are no more lines to return OR an error occured.

---
### 5. Line extraction.
```c
line = extract_line(stash, &stash);
```
Calls the helper function `extract_line()`to:
- Extract the next full line upto and including the newline character, if present, from `stash`.
- Save any leftover characters after the newline character into `leftover` for use in the next `get_next_line()` call.

---

<details>

<summary> Helper function extract_line() line by line breakdown </summary>
<br>

**Function prototype**

`char *extract_line(char *stash, char *leftover)`

`stash`
- Contains  the accumulated data read so far, including one or more potential lines.

`leftover`
- Static buffer to store characters after the newline (to be used in the next `get_next_line()` call)

**Variables**

`char *line``
- The final line that wil be extracted and returned.

`newline_ptr`
- Pointer to the first newline character found in `stash`.

`newline_index`
- Index of the newline character within `stash`, used for duplication.

**Logic**

```c
newline_ptr = ft_strchr(stash, '\n');
```
- Searches the `stash` for the first newline character.
- If found, `newline_ptr` points to it.
- If NOT found, `newline_ptr` is NULL.
<br>


```c
if (newline_ptr)
{
    newline_index = 0;
    while (stash[newline_index] != '\n')
        newline_index++;
```
If a newline is found;
- Loop through the `stash` to find its index.
- `newline_index` now holds the position of the first newline character.
<br>

```c
    line = ft_strldup(stash, newline_index + 1);
```
- Duplicate everything fom the beginning of `stash` up to and **including the newline character**, hence the +1.
<br>

```c
    ft_strlcpy(leftover, newline_ptr + 1, BUFFER_SIZE + 1);
````
Copies eveything **after** the newline (i.e. the remaining content) into `leftover`.
- `leftover` is static, so this content will persist until the next call.
- `BUFFER_SIZE + 1` ensures space for the null temrinator. 
<br>

```c
}
else
{
    line = ft_strdup(stash);
    leftover[0] = '\0';
}
```
If NO newline is found, meaning EOF has been reached and we are returning the final line, which does not end in a newline character;
- Duplicate the entire `stash` into `line`

Then clear leftover by setting it to an empty string.
<br>
<br>

```c
return (line);
````
Finally return the extracted line.

Exit function.

</details>


---
### 6. Free and Return
```c
free (buf);
free (stash);
```
- Free the temporary buffer `buf` that was allocated for reading data.
- Free the dynamically allocated `stash` string.
<br>

```c
return (line);
```
Return the extracted line.

End of `get_next_line()`.

</details>

---

## Bonus (v.2)
The bonus implementation supports multiple file descriptors by using a linked list of nodes. Each node holds a file descriptor, its associated leftover buffer, and a pointer to the next node.
This allows get_next_line() to maintain independent read states for each descriptor, enabling concurrent reads without interference—all while adhering to the constraint of using only one static variable.

<details>

<summary>Line by line breakdown</summary>

### 1. Struct
```c
typedef struct s_fd_node
{
	int			fd;
	char                    *stash;
	struct s_fd_node	*next;
} t_fd_node;
```
Creating a linked list where each node represents an open file descriptor is essential when handling multiple file descriptors. By dynamically creating and linking nodes as needed, the progam can manage an arbitrary number of simultaneous file reads. 

Each node stores the file descriptor `fd`, a `stash` buffer that holds leftover data between reads, and a pointer `next` to the next node in the list. 

This allows the function to independantly track the reading state of reach file, so data from one descriptor doesnt interfere with another.

---
### 2. Variables
`static t_fd_node   *head;` 

- Pointer to the head of the linked list of file descriptor nodes. Since it is static, it retains its value between calls, so the list of open files and thei buffers persist as long as the program runs or until the nodes are removed. 
<br>

`t_fd_node  *current;`

- Pointer to the node coresponding to the file descriptor passed to `get_next_line()`. It either points to an existing node or a newly created one, representing the file being read. 
<br>

`char  *buf;`

- A temporary buffer allocated each time `get_next_line()`is called. Used to store data read from the file descriptor before appending it to the stash. Has the size of `BUFFER_SIZE + 1` to accommodate a null terminator. 
<br>

`char  *line;`

- Holds the line extracted from the stash, which will be returned by the function. It contains either a line ending in a newline character or the remaining data at EOF *(end of file)*

---
### 3. Find / create node.
```c
current = find_or_create_node(&head, fd);
```
This line calls a helper function to locate the linked list node corresponding to the given file descriptor. 
- If such a node already exists in the list *(meaning we have previously read from this fd)*, it returns a pointer to that node. 
- If no node is found, it creates a new node, initializes its fields (sets the `fd`, creates an empty stash, and sets `next`to NULL), and adds it to the linked list.

So after this call, `current` points to the node managing the reading state for the requested `fd`.

*Passing `&head` allows the function to modify the actual head pointer itself (such as when adding the first node to an empty list), whereas passing just head would only modify a local copy without affecting the original list.*
<br>

---
<details>

<summary>Helper function find_or_create_node() line by line breakdown.</summary>
<br>

`t_fd_node  **node;` 

- Declares a pointer to a pointer of type `t_fd_node`, allowing us to traverse the linked list while keeping track of the address of the pointer that points to the current node.
<br>

```c
node = head;
```
- Initializes `node` to point to the head pointer of the linked list.
<br>

```c
while (*node && (*node)->fd != fd)
	node = &(*node)->next;
```
- Traverses the linked list by moving `node`to the address of the `next` pointer of the current node.
- Stopping if it finds a node where `fd`matches or reaches the end of the linked list.
<br>

```c
if (!*node)
{
```
- If we reach the end of the linked list without finding the `fd`, this means no node for this `fd`exists yet, so we must create it and add it to the list. 
<br>

```c
	*node = malloc(sizeof(t_fd_node));
````
- Allocates memory for the new node using malloc().
<br>

```c
	(*node)->fd = fd;
```
- Initializes the new nodes `fd` with the requested file descriptor.
<br>

```c
	(*node)->stash = ft_strdup("");
```
- Initializes the new nodes `stash`to an empty string.
<br>

```c
	(*node)->next = NULL;
}
```
- Sets the new nodes `next` pointer to NULL, since this will be the last node for now.
<br>

```c
return (*node);
```
- Returns the pointer to the found or newly created node.
</details>
---
### 4. Reading the file.
```c
buf = malloc(BUFFER_SIZE + 1);
```
- Dynamically allocates memory for the temporary buffer `buf`. This buffer is used in the subsequent read calls to temporarily hold chunks of data before appending them to the stash.

- `BUFFER_SIZE`is a predetermined constant that determines how many bytes to read at a time. This can be adjusted by compiling the program using the define flag `-D`. `cc main.c -D BUFFER_SIZE=9999`.
- The `+1` is to allocate space for a null termintor, so the buffer can be treated as a valid string after reading.
<br>

```c
current->stash = read_operation(fd, buf, current->stash);
```
Calls a helper function to read data from the file descriptor `fd` into the temporary buffer `buf`, then appends the data to the existing stash `current->stash`.

- `read_operation()` reads `BUFFER_SIZE` chunks of data from `fd` into `buf`. 

- - It then concatenates the read data (`buf`) to the existing stash (`stash`), preseving data from previous reads.

- - After each read, it searches the contents of `stash` for a newline character. 

- - Once a newline character is found OR the end of the file is reached, the contents of `stash` are returned and assigned back to the current nodes stash.

---

<details>

<summary> Helper function read_operation() line by line breakdown.</summary>
<br>

`int	bytes_read;`
- Stores how many bytes were read from the file descriptor.

`char *temp_stash;`
- Will temporarily hold the result of concatenating the old stash and buffer. 
<br>


```c
while (1)
{
```
Begins an infinite loop which will only break if a newline character is found in `stash`or reading is done (EOF or error).
<br>
<br>


```c
	bytes_read = read(fd, buf, BUFFER_SIZE);
```
Reads upto `BUFFER_SIZE`bytes from `fd` into `buf`.
- `bytes_read` will be:
- - `> 0`: Number of bytes read.
- - `== 0`: End of file (EOF).
- - `< 0`: read error.
<br>
<br>

```c
	if (bytes_read <= 0)
		buf[0] = '\0';
	else
		buf[bytes_read] = '\0';
```
- If no data is read (EOF or error), `buf` is set to an empty string.
- If data is read, a null terminator is added so that `buf` is a valid string.
<br>
<br>


```c
    temp_stash = ft_strjoin(stash, buf);
    free(stash);
    stash = temp_stash;
```
- Concatenates the old stash with the new buffer string using `ft_strjoin()`, which retruns a dynamically allocated string. Stores the new string in `temp_stash`.
- Frees the old `stash` to avoid memory leaks.
- Updates `stash` with the newly combined string.
<br>
<br>

```c
	if (ft_strchr(stash, '\n') != NULL || bytes_read <= 0)
		break ;
}
```
Break the loop if:
- the updated `stash` contains a newline character. This means we have enough data to extract the full line.
- we hit EOF or recieve a read error (`bytes_read <= 0`). 

Otherwise loop again until the break condition is met.
<br>
<br>

```c
return (stash);
```
When the loop ends, the final `stash`is returned. 

</details>

---

### 5. Nothing to return

```c
if (current->stash == NULL || *current->stash == '\0')
{
```
Checks wheather the current nodes `stash` is:
- NULL: Meaning memory allocation failed or it was never initialized.
- An empty string, meaning no meaningful data was read from the file.

If either condition is true, there is no line to return. 
<br>
<br>

```c
	free (buf);
	ft_remove_node_fd(&head, current);
	return (NULL);
}
```
Clean up and exit.
- `free(buf)`: Frees the temporary buffer to avoid memory leaks.
- `ft_remove_node(&head, current)`: Removes this file descriptors node fom the linked list, using a helper function.
- `return (NULL)`: Returns NULL to indicate no line could be read.

---

<details>

<summary> Helper function ft_remove_node() line by line breakdown </summary>

<br>

`t_fd_node  *previous;`
- A pointer which will track the node that comes before the node that we want to remove. This is necessary since we must update its `next` pointer to skip over the `current` node.
<br>


```c
if (*head == NULL || current == NULL)
	return ;
```
NULL check to avoid unnecessary operations.
- If the list is empty or `current` is invalid, there is nothing to free.
<br>


```c
if (*head == current)
	{
````
- Checks if the node to remove is the first in the list.
<br>


```c
	*head = (*head)->next;
```
Sets the head of the list to the next node.
- In a singly linked list, the head pointer points to the first node in the list. If the node we want to remove is that first node, we need to move the head pointer to the next node, so the list no longer includes the one we’re deleting.
<br>


```c
	free(current->stash);
	free(current);
}
````
- Free the `stash` of the node, since it was dynamically allocated.
- Free the node.
<br>


```c
else
{
	previous = *head;
		while (previous && previous->next != current)
			previous = previous->next;
```
If the node we want to remove is NOT the head of the linked list, we must find the node that comes before `current`.
- First set node `previous` to the start of the linked list.
- Traverse the list to find the node that comes before the `current` node that we want to remove.
- Once `previous->next` points to `current`, we have found the node that comes before the node we wish to remove. Exit the while loop.
<br>


```c
	if (previous)
```
Confirms that we have found a valid node, specifically the node that comes before the `current` node.
<br>


```c
	{
		previous->next = current->next;
		free(current->stash);
		free(current);
	}
```
- Links `previous` to the node that comes after `current`.
- Frees the `stash` of the node we are removing.
- Frees the node we want to remove.
<br>


```c
return ;
```
- Once the correct node has been found, the list has been relinked, and the node plus its contents have been freed, we can exit the function. 

</details>

---

### 6. Something to return (extract line)

```c
line = extract_line(current->stash, &current->stash);
```
This line calls the helper function `extract_line()` to:
- Extract a complete line from the current `stash`, including the newline character if present. The extracted line is then assigned to `line`, which will be returned from `get_next_line()`.
- Update the `stash` with whatever content remains after that line.

---

<details>

<summary> Helper function extract_line() line by line breakdown. </summary>
<br>

**Function prototype**


`char *extract_line(char *stash, char **updated_stash)`
- `stash` Holds the accumulated data from the previous read operations.
- `updated_stash` is a pointer to the `stash` pointer so we can replace it with the leftover content after extracting the a line.

**Variables**

`char *line;`
- Will hold the extracted line that will be returned.

`char *newline_i_ptr;`
- Pointer to the first `\n` character (if any).


`int newline_index;`
- The index / position of the newline character in the `stash` string.
<br>

**Logic**


```c
newline_i_ptr = ft_strchr(stash, '\n');
```
Searches for the first occurance of `\n` in `stash`.
- If found, `newline_i_ptr` points to it.
- If not, `newline_i_ptr` is NULL.
<br>

```c
if (newline_i_ptr)
{
	newline_index = 0;
	while (stash[newline_index] != '\n')
		newline_index++;
```
If a newline character is found in `stash`;
- Calculate the position of the newline in `stash` and store the index number in `newline_index`.
<br>

```c
	line = ft_strldup(stash, newline_index + 1);
````
Duplicates the string **up to and including the newline character** and assigns the duplicated string to `line`.
<br>

```c
	*updated_stash = ft_strdup(newline_i_ptr + 1);
```
Copies everything **after** the newline character in `stash` into a new string.
- This becomes the updated `stash`, stored through the pointer `updated_stash`

TBC because I found a new way to handle updating stash, and I want to write the doc based on that. 

</details>

---


</details>

---