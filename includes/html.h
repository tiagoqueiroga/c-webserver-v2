#ifndef H_HTML
#define H_HTML

#include "globals.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


char *open_html_file(const char *path);

int file_exists(const char *filename);

int is_file_cached(const char *filename);

#endif