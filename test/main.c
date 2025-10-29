#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "../get_next_line.h"

static void print_visible(const char *s)
{
    if (!s)
    {
        printf("(null)");
        return;
    }
    for (size_t i = 0; s[i] != '\0'; ++i)
    {
        unsigned char c = (unsigned char)s[i];
        if (c == '\n')
            printf("\\n");
        else if (c == '\t')
            printf("\\t");
        else if (c < 32 || c == 127)
            printf("\\x%02X", c);
        else
            putchar(c);
    }
}

static void usage(const char *prog)
{
    fprintf(stderr,
            "Usage: %s <file> [max_lines]\n"
            "  Reads lines using get_next_line and prints them clearly.\n"
            "  BUFFER_SIZE=%d\n",
            prog, BUFFER_SIZE);
}

int main(int argc, char **argv)
{
    const char *path;
    long max_lines = -1; // -1 = no limit

    if (argc < 2)
    {
        usage(argv[0]);
        return 1;
    }
    path = argv[1];
    if (argc >= 3)
    {
        char *end = NULL;
        max_lines = strtol(argv[2], &end, 10);
        if (end == argv[2] || max_lines < 0)
        {
            fprintf(stderr, "Invalid max_lines: %s\n", argv[2]);
            return 1;
        }
    }

    int fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "open(%s) failed: %s\n", path, strerror(errno));
        return 1;
    }

    printf("Reading file: %s (BUFFER_SIZE=%d)\n", path, BUFFER_SIZE);

    char *line = NULL;
    size_t i = 0;
    while (max_lines < 0 || (long)i < max_lines)
    {
        line = get_next_line(fd);
        if (!line)
        {
            printf("[%zu] NULL (EOF)\n", i);
            break;
        }
        size_t len = ft_strlen(line);
        int ends_with_nl = (len > 0 && line[len - 1] == '\n');
        printf("[%zu] len=%zu ends_with_nl=%s: \"", i, len, ends_with_nl ? "yes" : "no");
        print_visible(line);
        printf("\"\n");
        free(line);
        ++i;
    }

    close(fd);
    return 0;
}
