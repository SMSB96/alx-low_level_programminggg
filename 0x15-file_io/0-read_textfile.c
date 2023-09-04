#include "main.h"
#include <stdlib.h>

/**
 * read_textfile- Read text from a file and prints it to STDOUT.
 * @filename: text file being read
 * @letters: number of bytes to be read
 * Return: The actual number of letters read and printed, or 0 on failure
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	char *buf;
	ssize_t fd;
	ssize_t bytes;
	ssize_t t;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	buf = malloc(sizeof(char) * letters);
	t = read(fd, buf, letters);
	bytes = write(STDOUT_FILENO, buf, t);

	free(buf);
	close(fd);
	return (bytes);
}
