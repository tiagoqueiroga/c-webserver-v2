#include "includes/request.h"
#include "includes/html.h"

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

void handle_get_request(Request *request)
{
    char *html = "";

    if(strcmp(request->path, "/") == 0)
    {
        html = open_html_file("index.html");
    }else{
        html = open_html_file(request->path);
    }

    if(html == NULL)
    {
        send(request->client_socket, "HTTP/1.0 404 Not Found\r\n\r\n", 26, 0);
        send(request->client_socket, "404 Not Found", 13, 0);
        return;
    }


    send(request->client_socket, OK_STATUS_RESPONSE, strlen(OK_STATUS_RESPONSE), 0);
    send(request->client_socket, html, strlen(html), 0);

}
