# get_next_line

Summary
-------
`get_next_line` provides a function to read one line at a time from a file descriptor. It handles partial reads and internal buffering to return complete lines on each call.

Features
--------
- Read lines from any file descriptor
- Handles buffer management and leftover data between calls

Requirements
------------
- Linux
- `gcc`

Build
-----
This is generally a single-source utility. Compile into a test program or include in other projects. Example flags used across projects:

```
gcc -Wall -Wextra -Werror -g3 get_next_line.c get_next_line_utils.c -o gnl_test
```

Usage
-----
Run the test program or integrate the `get_next_line` functions in your codebase. The function prototype is usually:

```
char *get_next_line(int fd);
```

Project Layout
--------------
- `get_next_line.c`, `get_next_line_utils.c` — implementation files
- `get_next_line.h` — header

Notes
-----
- Remember to free the returned string after use. Behavior with different `BUFFER_SIZE` values can be tested by compiling with a different macro.

Author / Attribution
--------------------
Author: ankammer

License
-------
Unlicensed.
