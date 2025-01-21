#ifndef H_SERVER
#define H_SERVER

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define LOCALHOST "127.0.0.1"
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 5

const char *initial_line = "HTTP/1.0 200 OK\r\n\r\n";
const char *response = "<h1>Hi there</h1>";
const char *html_public_folder = "html";

char buffer[BUFFER_SIZE];

typedef struct sockaddr_in s_sockaddr_in;

typedef struct
{
    char method[8];
    char path[256];
    char version[16];
    char host[256];
    char user_agent[256];
    char accept[256];
    char accept_language[256];
    char accept_encoding[256];
} Request;

int create_socket(const char *port);

char *open_html_file(const char *path);

void handle_request(char *buffer, int client_socket);

#endif