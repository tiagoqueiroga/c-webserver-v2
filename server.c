#include "includes/server.h"

/*
  TODO:
    1 - Create a simple way to read the static html file and handle the response with it
    2 - Parse the request to a struct like(Request)
    3 - Handle the request with the struct
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

char *open_html_file(const char *path)
{

  char location[256];
  char file_buffer[BUFFER_SIZE];

  char *file_text = malloc(BUFFER_SIZE + 1);

  snprintf(location, sizeof(location), "%s/%s", html_public_folder, path);

  FILE *file = fopen(location, "r");

  if (file == NULL)
  {
    perror("failed to open file");
    exit(EXIT_FAILURE);
  }

  while (read(fileno(file), file_buffer, BUFFER_SIZE) > 0)
  {
    strcat(file_text, file_buffer);
  }

  fclose(file);

  return file_text;
}

void handle_request(char *buffer, int client_socket)
{
  printf("Handling request: %s \n", buffer);

  Request *request;

  request = malloc(sizeof(Request));
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
      printf("Server received %ld bytes\n", recv_len);
      printf("%s\n", buffer);

      handle_request(buffer, client_fd);

      char *html = open_html_file("index.html");

      // can you explain why I send the initial line and the html separately?
      send(client_fd, initial_line, strlen(initial_line), 0);
      send(client_fd, html, strlen(html), 0);
    }

    close(client_fd);
  }

  return EXIT_SUCCESS;
}
