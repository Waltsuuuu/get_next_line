# get_next_line

`get_next_line` is a function written in C that reads a file or standard input one line at a time. It returns a freshly allocated string containing the next line each time it's called, including the newline character (`\n`) if present.

The implementation uses a static buffer (`stash`) to keep leftover data between calls, and reads from the file descriptor using the `read()` system call with a customizable buffer size (`BUFFER_SIZE`).

***Note***
- The use of *lseek()* and global variables was forbidden for this project.

### Example Usage
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
## Line-by-Line breakdown. 
### 1. Variable declarations
`char *buf`
	Buffer to store the contents read by the read() operation.

`static char *stash`
	A persistent buffer to store the contents read into buf during the read() operations.

`char *line`
	Pointer to the line that will be returned. Up to and containing the newline or end of file.

---
### 2. Memory allocation
```c
buf = malloc(BUFFER_SIZE + 1);
```
Allocate memory for the buffer *buf* using malloc().

*BUFFER_SIZE is a macro defined in the header file (get_next_line.h). It is set to 32 bytes, but it can also be changed by compiling with `-D` flag;*
    
    `cc main.c -D BUFFER_SIZE=9999`

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
Read the file `BUFFER_SIZE` chunks and store the chunks in *stash*, until we find a newline `\n` in *stash*.
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

---
