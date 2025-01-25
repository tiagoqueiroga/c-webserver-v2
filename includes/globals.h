#ifndef H_GLOBALS
#define H_GLOBALS

#include <stdlib.h>
#include "request.h"

#define MAX_HEAP_REQUESTS 256
#define MAX_HTML_FILES 256
#define MAX_HTML_FILE_SIZE 1024

typedef struct
{
    char name[256];
    char *file_text[MAX_HTML_FILE_SIZE];
    size_t file_size;
} HtmlFile;

typedef struct
{
    HtmlFile *files[MAX_HTML_FILES];
    size_t length;
} HtmlFileArray;

typedef struct
{
    Request *request[MAX_HEAP_REQUESTS];
    HtmlFileArray *htmls;
} Data;

extern Data *data;

void init_data(void);

void free_data(void);

#endif