*This project has been created as part of the 42 curriculum by maratana.*

# get_next_line

## Description

**get_next_line** is a 42 project focused on file handling in C. The goal is to create a function that reads and returns one line at a time from a file descriptor.

The function must handle different buffer sizes, preserve unread data between calls, and correctly manage EOF and errors.

## Instructions

### Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c
```

Change `BUFFER_SIZE` to test different reading sizes.

### Usage

```c
#include "get_next_line.h"

int fd = open("test.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)))
{
    printf("%s", line);
    free(line);
}
close(fd);
```

**Function prototype:**

```c
char *get_next_line(int fd);
```

## Resources

linux man pages
chatgpt used for research and exploration of new concepts 

## Algorythmic Choices

- **Static variable:** Preserves unread data between function calls.
- **Buffer-based reading:** Reads data in chunks using `read()`.
- **Dynamic allocation:** Allows lines of arbitrary length.
- **Memory management:** Frees temporary buffers and previously allocated memory when no longer needed.