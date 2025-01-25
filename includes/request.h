#ifndef H_REQUEST
#define H_REQUEST

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

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
    int  client_socket;
} Request;

#define OK_STATUS_CODE  "200"
#define OK_STATUS_RESPONSE  "HTTP/1.0 200 OK\r\n\r\n"

void dump_request(Request *request);

Request * create_request();

Request *parse_request(Request *request, char *buffer, int client_socket);

void handle_get_request(Request *request);

#endif