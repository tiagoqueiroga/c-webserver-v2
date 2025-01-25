#include "includes/utils.h"

char *strlower(char *str)
{
    for (size_t i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }

    return str;
}

char * strcopy(const char *str)
{
    char *new_str = malloc(strlen(str) + 1);

    if (new_str == NULL)
    {
        //perror("failed to allocate memory for new string");
    }

    strcpy(new_str, str);

    return new_str;
}