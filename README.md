_This project has been created as part of the 42 curriculum by klucchin_

DESCRIPTION: The get_next_line is a function who is able to read form a file descriptor and write it line by line.

The get_next_line_bonus function acts the same but can manage multiple file descriptors at the same time using only 1 static variable.

By using some functions already coded from my libft, adjusting strjoin to prevent leaks, and creating some gnl specific functions that can write a line, keep in memory the excess if there is one, deleting the line that was printed, put the excess to the begining of the new line, and everything by managing the size of BUFFER_SIZE.

INSTRUCTIONS: It must be compiled with cc and flags -Wall -Werror -Wextra, and in order to change BUFFER_SIZE, -D BUFFER_SIZE="size".

To use the mandatory gnl compile get_next_line.c and get_next_line_utils.c

To use the bonus gnl compile get_next_line_bonus.c and get_next_line_utils_bonus.c

RESSOURCES: open, read ,close documentations were used to have a better understanding of how to manage a file descriptor.

websites like geeksforgeeks, stackoverflow and reddit were usefull to me for understanding static variables and the use of the functions mentionned below.

ALGORITHM: The goal of get_next_line is to return one line per function call, no matter how the data is split by read.
Because read may return partial fragments of a line, we need an algorithm that can accumulate, detect, extract, and preserve data between calls.

1 - Reading and filling the stash, we call read until a '\n' is reached, returns 0 if it's the end file or NULL if an error occurs. Thats why stash is declared as static so it persists between calls.

2 - Extracting new line,  after it was read, the memory is allocated and the string is copied including the '\n'. If there is no new line, the entire stash is returned.

3 - Removing the stash, after extracting the line only the leftover is kept in order to be copied later for the next call and free the old stash. If there is no leftover stash becomes NULL.