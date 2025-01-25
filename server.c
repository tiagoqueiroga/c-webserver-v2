#include "includes/server.h"
#include "includes/request.h"
#include "includes/globals.h"

/*
  TODO:
    1 - Create a simple way to read the static html file and handle the response with it
    2 - Parse the request to a struct like(Request)
*/

int create_socket(const char *port)
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd == -1)
  {
    perror("failed to create socket");
    return EXIT_FAILURE;
  }

  s_sockaddr_in server_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(port));
  server_addr.sin_addr.s_addr = inet_addr(LOCALHOST);

  struct sockaddr *bind_addr = (struct sockaddr *)&server_addr;

  // add socket option to reuse the address
  int opt = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
  {
    perror("setsockopt failed");
    exit(EXIT_FAILURE);
  }

  if (bind(sockfd, bind_addr, sizeof(server_addr)) == -1)
  {
    perror("failed to bind");
    exit(EXIT_FAILURE);
  }

  if (listen(sockfd, MAX_CLIENTS) == -1)
  {
    perror("failed to listen");
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d\n", atoi(port));

  return sockfd;
}

void handle_request(char *buffer, int client_socket)
{
  Request *r;

  r = create_request();

  parse_request(r, buffer, client_socket);

  if(strcmp(r->method,"GET") == 0){
    handle_get_request(r);
  }

  #ifdef DEBUG
    dump_request(r);
  #endif

}


int main(int argc, char *argv[])
{

  int server_fd;

  if (argc != 2)
  {
    printf("Usage: ./server <PORT>\n");
    exit(EXIT_FAILURE);
  }

  char *port = argv[1];

/* Init global data on the heap */
  init_data();

  server_fd = create_socket(port);

  for (;;)
  {
    int client_fd = accept(server_fd, NULL, NULL);

    if (client_fd == -1)
    {
      perror("failed to create client socket");
      exit(EXIT_FAILURE);
    }

    size_t recv_len = recv(client_fd, buffer, BUFFER_SIZE, 0);

    if (recv_len > 0)
    {      
      handle_request(buffer, client_fd);
    }

    close(client_fd);
  }


  free_data();

  return EXIT_SUCCESS;
}
