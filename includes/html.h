#ifndef H_HTML
#define H_HTML

#include "globals.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

char *open_html_file(const char *path);

int file_exists(const char *filename);

int is_file_cached(const char *filename);

int cache_file(const char *filename, const char *file_text);

HtmlFile *get_html_file(const char *filename);

#endif