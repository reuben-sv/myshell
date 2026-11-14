#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
size_t my_strlen(const char *s)
{
    size_t count = 0;
    while (*s != '\0')
    {
        s++;
        count++;
    }
    return count;
}
int word_count(const char *s)
{
    const unsigned char *news = (const unsigned char *)s;
    int count = 0;
    while (*news != '\0')
    {
        if (!isspace(*news) && (isspace(*(news + 1)) || *(news + 1) == '\0'))
        {
            count += 1;
        }
        news++;
    }
    return count;
}

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
int old_main(void)
{
    struct
    {
        const char *input;
        int expected;
    } tests[] = {
        {"  hello   world ", 2},
        {"", 0},
        {"a1", 1},
        {"ls -la .", 3},
        {"cat file.txt", 2},
        {"\t tab\tseparated\n", 2}
        // ... add yours
    };
    int num_tests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < num_tests; i++)
    {
        int actual = word_count(tests[i].input);
        if (actual != tests[i].expected)
        {
            printf("Test %d FAILED! Input: '%s', Expected: %d, Got: %d\n",
                   i, tests[i].input, tests[i].expected, actual);
        }
        else
        {
            printf("Test %d PASSED! Input: '%s', Expected: %d, Got: %d\n",
                   i, tests[i].input, tests[i].expected, actual);
        }
    }
    printf("=================> new count function\n");

    for (int i = 0; i < num_tests; i++)
    {
        int new_actual = word_count_new(tests[i].input);
        if (new_actual != tests[i].expected)
        {
            printf("Test %d FAILED! Input: '%s', Expected: %d, Got: %d\n",
                   i, tests[i].input, tests[i].expected, new_actual);
        }
        else
        {
            printf("Test %d PASSED! Input: '%s', Expected: %d, Got: %d\n",
                   i, tests[i].input, tests[i].expected, new_actual);
        }
    }
    return 0;
}

int main(void)
{
    char buffer[1024];
    bool valid;
    while (true)
    {
        valid = true;
        printf("mysh> ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            printf("\n");
            break;
        }
        const size_t index = strcspn(buffer, "\n");

        if (buffer[index] == '\n')
        {
            buffer[index] = '\0';
        }
        else if (!feof(stdin))
        {
            int c = getchar();
            if (c != EOF && c != '\n')
            {
                fprintf(stderr, " input is too long\n");
                valid = false;
                while ((c = getchar()) != '\n' && c != EOF)
                {
                    /* Loop runs until the rest of the line is fully discarded */
                }
            }
        }

        if (valid)
        {
            const char *s = &buffer[0];
            const int wordcount = word_count_new(s);
            if (wordcount != 0)
            {
                printf("\tYou typed:%s\n", buffer);
            }
        }
        fflush(stdout);
    }
    return 0;
}
// give this to claude. commit it as implement repl loop and handle input too large