# get_next_line

This readme is not finished.

`get_next_line` is a function written in C that reads a file or standard input one line at a time. It returns a freshly allocated string containing the next line each time it's called, including the newline character (`\n`) if present. The use of *lseek()* and global variables was forbidden for this project.

This repository contains two versions of the `get_next_line()` function.


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
The first version of this function was created with only one file descriptor in mind. A single static character array is used to store the leftover read data from the file descriptor. Meaning the the function must be called repeatedly until EOF before a new `fd` can be used. 
<details>
<summary>Line by line breakdown</summary>

### 1. Variable declarations
`char *buf`
	Buffer to store the contents read by the read() operation.

`static char *stash`
	A persistent buffer to store the contents read into buf during the read() operations.

`char *line`
	Pointer to the line that will be returned. Up to and containing the newline or end of file.

---
### 2. Buffer memory allocation
```c
buf = malloc(BUFFER_SIZE + 1);
```
Allocate memory for the buffer *buf* using malloc().

*`BUFFER_SIZE` is a macro defined in the header file (get_next_line.h), modifiable by compiling with `-D` flag;*

```
cc main.c -D BUFFER_SIZE=9999
```

+1 is added for the null terminator, as we need *buf* to be a valid string.
<br>
<br>
<br>

```c
if (stash == NULL)
```
Check if stash has been initialized.
<br>
<br>
<br>
```c
	stash = ft_strdup("");
```
If stash is NULL, we need to initialize *stash* to be an empty null terminated string. For this, we use our helper function ft_strdup().The function allocates memory and returns a duplicate of the string passed in as an argument. <br>

---

### 3. The read operation

```c
stash = read_operation(fd, buf, stash);
```
Read the file in `BUFFER_SIZE` chunks and store the chunks in *stash*, until we find a newline `\n` in *stash*.
<br>
<br>
<br>

***Inside the helper function***

```c
char	*read_operation(int fd, char *buf, char *stash)
```

read_operation() is a helper function which will read the file in chunks and store the read chunks into *stash*, after each read it will check if *stash* contains a newline (`\n`), once it detects a newline or hits the end of the file, it returns *stash*.
<br>
<br>
<br>

***read_operation() variables***

`int bytes_read` - *Store the number of bytes read during the read() operation. This will be used as the index for the *buf* null terminator OR an indicator that the file has been fully read, since read() returns 0 if there is nothing left to read.*

`char *temp_stash` - *Temporary pointer used to store the result of ft_strjoin, before assigning the result back to stash. Prevents memory leaks when updating stash.*
<br>
<br>
<br>

```c
while (1)
```
While (1), is an infinite loop. This loop will only stop if a break is found. In our case, break will be used when there is nothing left to read, or a newline is found in *stash*.
<br>
<br>
<br>

```c
bytes_read = read(fd, buf, BUFFER_SIZE);
```
Store the number of bytes read by the read() operation in the variable bytes_read.
Run the read() operation on the *fd* specified by the caller, storing the read contents into *buf* and only reading BUFFER_SIZE amount of bytes.
<br>
<br>
<br>

```c
if (bytes_read <= 0)`<br>
	buf[0] = '\0';
``` 
If the read() operation returned 0 or less, meaning the end of the file was found and nothing was stored in buf. We null terminate buf at index 0.
<br>
<br>
<br>

```c
else
    buf[bytes_read] = '\0';
```
If more than 0 bytes were read, we null terminate buf at the index specified by the number of bytes read. This index will be pointing to the memory slot after the last character in buf.
<br>
<br>
<br>

```c
temp_stash = ft_strjoin(stash, buf);
```
Concatenate the contents of *buf* into *stash* using the helper function *ft_strjoin()*. Storing the new string returned by *ft_strjoin* in *temp_stash*.
<br>
<br>
<br>

```c
free (stash);
```
Free the current contents of *stash*.
<br>
<br>
<br>

```c
stash = temp_stash;

```
Assign the new string made of *stash*+*buf*, which is stored in *temp_stash*, to *stash*.
<br>
<br>
<br>

```c
if (ft_strchr(stash, '\n') != NULL || bytes_read <= 0)
```
Check if *stash* contains a newline `\n`, using the helper function *ft_strchr()*<br>
OR<br>
if *bytes_read* is 0 or less, meaning the end of the file has been reached.
<br>
<br>
<br>

```c
	break ;
```
If true, use *break* to exit the while loop.<br>

If false, loop again.
Eventually a newline character will be found or the end of the file will be reached.
<br>
<br>
<br>

```c
return (stash);
```
Once the while loop ends, we will return stash.

---

### 4. End of file check / Error check.
```c
if (stash == NULL || *stash == '\0')
```
If the read() operation returned NULL or stash points to a null terminator. We have nothing to return to the caller. The end of the file has been reached or there has been an error reading the file.
<br>
<br>
<br>

```c
{
	free (buf);
	free (stash);
	stash = NULL;
	return (NULL);
}
```
If true, free() the buffer *buf* and *stash*.
<br>Then also set *stash* to NULL. This must be done since *free()* does not set *stash* to NULL. It just deallocates the memory, leaving *stash* as a dangling pointer: it still contains the same memory address, which now points to freed (invalid) memory.<br>
Finally return (NULL).

---
### 5. Line extraction.
```c
line = extract_line(stash, &stash);
```
The line variable will hold the portion of the *stash* string up to and containing the newline character OR up to the end of the file, if no newline is present.
<br>
<br>
<br>

***Inside the helper fucntion***
```c
char	*extract_line(char *stash, char **updated_stash)
```
extract_line() is a helper function that extracts the next line from stash, including the newline if present.
It also trims the extracted part from stash, saving the remainder in *updated_stash so stash can continue where it left off on the next call.


Why *****updated_stash?***<br>
- Even though stash is declared as static in get_next_line(), when passed by value to extract_line(), reassigning it (e.g., stash = ft_strdup(...)) only modifies the local copy of the pointer. The original stash in get_next_line() remains unchanged.
- By contrast, passing a pointer to stash, as char **updated_stash, lets extract_line() directly modify the original pointer. Doing *updated_stash = ft_strdup(...) updates the actual stash in get_next_line(), preserving the new value and avoiding memory issues.
<br>
<br>
<br>

***extract_line() variables***

`char *line`- *The extracted line we want to return.*

`char *newline_index` - *A pointer to the newline character in the stash string.*
<br>
<br>
<br>

```c
newline_index = ft_strchr(stash, '\n');
```
Find the index of the newline character in stash with the helper function ft_strchr() and store the index in newline_index.
<br>
<br>
<br>

```c
if (newline_index)
{
	line = ft_strldup(stash, count_chars_to_newline(stash));
	*updated_stash = ft_strdup(newline_index + 1);
}
```
If a newline is found in stash

Use *ft_strldup()* to copy the part up to and including the newline into *line*. `count_chars_to_newline()` returns the number of characters to the newline, this specifies the number of bytes we will duplicate from *stash* to *line*.

Then update *updated_stash with a duplicate of the remaining string after the newline using ft_strdup().
This trims the processed line from *stash* and keeps only what’s left for the next call.
<br>
<br>
<br>

```c
else
{
	line = ft_strdup(stash);
	*updated_stash = NULL;
}
```
If no newline is found in stash, the entire stash is our final line.

Create *line* by duplicating *stash*, using *ft_strdup()*.

Update *stash* to NULL. As we no longer need to store content inside it.
<br>
<br>
<br>

```c
return (line);
```
Return the extracted string - *line*, back to *get_next_line()*.

---
### 6. Free and Return
```c
free (buf);
```
Free the buf memory.
<br>
<br>
<br>

```c
return (line);
```
Return the extracted line.

Exit function.

</details>

---

## Bonus (v.2)
This bonus task was to modify the function to handle multiple file descriptors, while only using one static variable.

Here a struct is used to store the file descriptor, its associated `stash`, and a pointer to the next node, forming a linked list that tracks each file descriptors state seperately. This allows `get_next_line()` to manage multiple files simultaneously without interference. 

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

### 5. End of file / Error check.

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

### 6. Extract the return line from stash.

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


`char *extract_line(char **stash)`
- `stash` Pointer to the pointer of `stash`. Passing in the address of the pointer, we are able to update it with a new pointer that will point to the remaining content of `stash` once it has been trimmed. Dereferencing this will allow access to the values stored in `stash`. 



**Variables**

`char *trimmed_stash`
- Will temporarily store the remaining contents of `stash` that come after the newline. 

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
	while (*stash[newline_index] != '\n')
		newline_index++;
```
If a newline character is found in `stash`;
- Calculate the position of the newline in `stash` and store the index number in `newline_index`.
<br>

```c
	line = ft_strldup(*stash, newline_index + 1);
````
Duplicates the string **up to and including the newline character** and assigns the duplicated string to `line`.
<br>

```c
	trimmed_stash = ft_strdup(newline_i_ptr + 1);
```
Copies everything **after** the newline character in `stash` into a new string.
- Save the newly allocated string in `trimmed_stash`.
<br>

```c
	free(*stash);
	*stash = trimmed_stash;
```
- Free the old contents of `stash`.
- Update the `stash` pointer to point to the beginning of the new trimmed string.
<br>

```c
else
{
	line = ft_strdup(*stash);
	free(*stash);
	*stash = NULL;
}
```
If no newline is found in `stash`, there is no need to trim the stash. 
- Copy the remaining contents of `stash` to `line`.
- Free the contents of `stash`.
- Set stash to NULL, to prevent a dangling pointer.
<br>

```c
return (line);
```
Finally return the extracted `line` from `stash` and exit function.

</details>

---

### 7. Free and exit.

```c
free (buf);
return (line);
```
-Free the temporary buffer.
-Return the `line` read from `fd` to the caller.

</details>

