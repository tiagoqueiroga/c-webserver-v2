#include "includes/html.h"

#define BUFFER_SIZE 1024
#define HTML_PUBLIC_FOLDER "html"

int file_exists(const char *filename)
{
    struct stat file_buffer;

    return (stat(filename, &file_buffer) == 0);
}

char *open_html_file(const char *path)
{
    char location[256];
    char file_buffer[BUFFER_SIZE];

    snprintf(location, sizeof(location), "%s/%s", HTML_PUBLIC_FOLDER, path);

    if (file_exists(location) == 0)
    {
        return NULL;
    }

    if (is_file_cached(path) == 1)
    {
        printf("File is already cached\n");
    }

    char *file_text = malloc(BUFFER_SIZE + 1);

    if (file_text == NULL)
    {
        perror("failed to allocate memory for file text");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(location, "r");

    if (file == NULL)
    {
        perror("failed to open file");
        exit(EXIT_FAILURE);
    }

    while (read(fileno(file), file_buffer, BUFFER_SIZE) > 0)
    {
        strcat(file_text, file_buffer);
    }

    fclose(file);

    return file_text;
}

int is_file_cached(const char *filename)
{

    printf("Cached files: %ld \n", data->htmls->length);

    for (size_t index = 0; index < data->htmls->length; index++)
    {
        if (strcmp(data->htmls->files[index]->name, filename) == 0)
        {
            return 1;
        }
    }

    return 0;
}