#include "includes/request.h"


void dump_request(Request *request)
{
    printf("Dumping request:\n");
    printf("\tMethod: %s\n", request->method);
    printf("\tPath: %s\n", request->path);
    printf("\tVersion: %s\n", request->version);
    printf("\tHost: %s\n", request->host);
    printf("\tUser-Agent: %s\n", request->user_agent);
    printf("\tAccept: %s\n", request->accept);
    printf("\tAccept-Language: %s\n", request->accept_language);
    printf("\tAccept-Encoding: %s\n", request->accept_encoding);
    printf("\tClient Socket: %d\n", request->client_socket);
}


Request *create_request()
{
    Request *request;

    request = malloc(sizeof(Request));

    if (request == NULL)
    {
        perror("failed to allocate memory for request");
        exit(EXIT_FAILURE);
    }

    return request;
}

Request *parse_request(Request *request, char *buffer, int client_socket)
{
    sscanf(buffer, "%s %s %s %s %s %s %s %s",
           request->method,
           request->path,
           request->version,
           request->host,
           request->user_agent,
           request->accept,
           request->accept_language,
           request->accept_encoding);
    
    request->client_socket = client_socket;

    return request;
}

