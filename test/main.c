#include <stdio.h>
#include <errno.h>

#include "../get_next_line.h"

int main(void)
{
	int fd;
	char *line;
	char *error;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	error = get_next_line(-1);
	if (error == NULL)
		printf("Correctly handled invalid file descriptor\n");
	else
		printf("Failed to handle invalid file descriptor\n");

	while ((line = get_next_line(1	))) // change fd to 1 for stdout
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
// cd test
// gcc -Wall -Wextra -Werror main.c ../get_next_line.c ../get_next_line_utils.c -o demo
// ./demo
