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

    char *file_text = malloc(BUFFER_SIZE + 1);

    if (file_text == NULL)
    {
        perror("failed to allocate memory for file text");
        exit(EXIT_FAILURE);
    }

    snprintf(location, sizeof(location), "%s/%s.html", HTML_PUBLIC_FOLDER, path);

    if (file_exists(location) == 0)
    {
        #ifdef DEBUG
                printf("File %s does not exist\n", path);
        #endif

        return NULL;
    }

    /*
    if (is_file_cached(path) == 1)
    {
        HtmlFile *cached = get_html_file(path);

        #ifdef DEBUG
            printf("File %s is already cached\n", path);
        #endif

        return *cached->file_text;
    }

    if (file_text == NULL)
    {
        perror("failed to allocate memory for file text");
        exit(EXIT_FAILURE);
    }
    */

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

    if (cache_file(path, file_text) == -1)
    {
        perror("failed to cache file");
        exit(EXIT_FAILURE);
    }

    fclose(file);

    return file_text;
}

int is_file_cached(const char *filename)
{
    char *filename_lowercase = strcopy(filename);
    
    for (size_t index = 0; index < data->htmls->length; index++)
    {
        
        HtmlFile *cached = data->htmls->files[index];

        if (strcmp(cached->name, filename_lowercase) == 0)
        {
            return 1;
        }
      
    }

    return 0;
}

int cache_file(const char *filename, const char *file_text)
{

    HtmlFile *html_file = malloc(sizeof(HtmlFile));

    if (html_file == NULL)
    {
        perror("failed to allocate memory for html file");
        return -1;
    }

    strncpy(html_file->name, filename, strlen(filename));
    *html_file->file_text = file_text;

    data->htmls->files[data->htmls->length] = html_file;

    data->htmls->length++;

    return 0;
}

HtmlFile *get_html_file(const char *filename){
    char *filename_lowercase = strcopy(filename);
    
    for (size_t index = 0; index < data->htmls->length; index++)
    {
        
        HtmlFile *cached = data->htmls->files[index];

        if (strcmp(cached->name, filename_lowercase) == 0)
        {
            return cached;
        }
      
    }

    return NULL;
}
