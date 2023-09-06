#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

char *create_buffer(void);
void close_file(int fd);
void copy_file(int from, int to, char *buffer);

/**
 * main - Entry point of the file copy program.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success, 97 on incorrect number of arguments,
 *         98 on read error, 99 on write error, 100 on close error.
 */
int main(int argc, char *argv[])
{
	int from, to;
	char *buffer;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	buffer = create_buffer();
	from = open(argv[1], O_RDONLY);
	to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

	if (from == -1 || to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file\n");
		free(buffer);
		close_file(from);
		close_file(to);
		exit(98);
	}

	copy_file(from, to, buffer);

	free(buffer);
	close_file(from);
	close_file(to);

	return (0);
}

/**
 * create_buffer - Allocates a buffer for reading/writing.
 *
 * Return: A pointer to the newly-allocated buffer.
 */
char *create_buffer(void)
{
	char *buffer = malloc(BUFFER_SIZE);

	if (buffer == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Memory allocation failed\n");
		exit(99);
	}
	return (buffer);
}

/**
 * close_file - Closes a file descriptor.
 * @fd: The file descriptor to be closed.
 */
void close_file(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * copy_file - Copies the content from one file descriptor to another.
 * @from: The source file descriptor.
 * @to: The destination file descriptor.
 * @buffer: The buffer used for reading/writing.
 */
void copy_file(int from, int to, char *buffer)
{
	ssize_t r, w;

	while ((r = read(from, buffer, BUFFER_SIZE)) > 0)
	{
		w = write(to, buffer, r);
		if (w == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to file\n");
			exit(99);
		}
	}

	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file\n");
		exit(98);
	}
}

