/*  The tee command reads its standard input until end-of-file, writing a copy of the input
    to standard output and to the file named in its command-line arguments. (We show
    an example of the use of this command when we discuss FIFOs in Section 44.7.)
    Implement tee using I/O system calls. By default, tee overwrites any existing file with
    the given name. Implement the -a command-line option (tee -a file), which causes tee
    to append text to the end of a file if it already exist. (Refer to Appendix B for a
    description of the getopt() function, which can be used to parse command-line
    options.)
*/

#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#define MAX_READ  8 * 3

int main(int argc, char **argv)
{
    ssize_t rd, wr;
    char buffer[MAX_READ];

    rd = wr = 0;

    while ((rd = read(STDIN_FILENO, buffer, MAX_READ)) > 0) {
        if (rd == -1) {
            fprintf(stderr, "read(): %s\n", strerror(errno));
            exit(EXIT_FAILURE); 
        }

        wr = write(STDOUT_FILENO, buffer, MAX_READ);
        if (wr <= 0) {
            fprintf(stderr, "write(): %s\n", strerror(errno));
            exit(EXIT_FAILURE); 
        }
    }
    return 0;
}