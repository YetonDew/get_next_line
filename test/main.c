#include <stdio.h>
#include <errno.h>

#include "../get_next_line.h"

int main(void)
{
	int fd;
	char *line;
	char *error;

	fd = open("test.txt", O_RDONLY);
	error = get_next_line(-1);
	if (error == NULL && errno == EBADF)
		printf("Correctly handled invalid file descriptor\n");
	else
		printf("Failed to handle invalid file descriptor\n");

	while ((line = get_next_line(fd)) != NULL) // change fd to 1 for stdout
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
