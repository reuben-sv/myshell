#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int word_count_new(const char *s)
{
    const unsigned char *news = (const unsigned char *)s;
    bool is_inside = false;
    int count = 0;
    while (*news != '\0')
    {
        if (!isspace(*news) && !is_inside)
        {
            count += 1;
            is_inside = true;
        }
        else if (isspace(*news))
        {
            is_inside = false;
        }
        news++;
    }
    return count;
}

bool read_input(char *buffer, size_t size)
{
    printf("mysh> ");
    fflush(stdout);
    if (fgets(buffer, size, stdin) == NULL)
    {
        return false;
    }
    const size_t index = strcspn(buffer, "\n");

    if (buffer[index] == '\n')
    {
        buffer[index] = '\0';
        return true;
    }

    int c = getchar();
    if (c != EOF && c != '\n')
    {
        fprintf(stderr, " input is too long\n");
        while ((c = getchar()) != '\n' && c != EOF)
        {
            /* Loop runs until the rest of the line is fully discarded */
        }
        return false;
    }

    return true;
}

int main(void)
{
    char buffer[1024];

    while (true)
    {

        if (!read_input(buffer, sizeof(buffer)))
        {
            if (feof(stdin))
            {
                printf("\n");
                break;
            }
            continue;
        }

        const char *s = &buffer[0];
        const int wordcount = word_count_new(s);
        if (wordcount != 0)
        {
            printf("\tYou typed:%s\n", buffer);
        }
    }
    return 0;
}
// give this to claude. commit it as implement repl loop and handle input too large