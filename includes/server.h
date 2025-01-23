#ifndef H_SERVER
#define H_SERVER

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "globals.h"
#include "request.h"

#define LOCALHOST "127.0.0.1"
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 5

const char *response = "";
const char *html_public_folder = "html";

char buffer[BUFFER_SIZE];

typedef struct sockaddr_in s_sockaddr_in;

int create_socket(const char *port);

char *open_html_file(const char *path);

void handle_request(char *buffer, int client_socket);

#endif