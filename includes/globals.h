#ifndef H_GLOBALS
#define H_GLOBALS

#include <stdlib.h>
#include "request.h"

#define MAX_HEAP_REQUESTS 256
#define MAX_HTML_FILES 256

typedef struct
{
    char name[256];
    char *file_text;
    size_t file_size;
} HtmlFile;

typedef struct
{
    HtmlFile **files;
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