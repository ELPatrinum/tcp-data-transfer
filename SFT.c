#include "SFT.h"

void ft_send_file(FILE *fp, int sockfd)
{
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL)
  {
    if (send(sockfd, data, sizeof(data), 0) == -1)
    {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

int ft_client(void)
{
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;

  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  char *filename;
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
  {
  perror("[-]Error in socket");
  return(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1)
  {
  perror("[-]Error in socket");
  return(1);
  }
  printf("[+]Connected to Server.\n");

  printf("Write the file name\n");
  filename = get_next_line(0);
  filename[strcspn(filename, "\n")] = '\0';
  printf("FILENAME:%s:\n", filename);
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    perror("[-]Error in reading file.");
    return(free(filename), 1);
  }

  ft_send_file(fp, sockfd);
  printf("[+]File data sent successfully.\n");
  free(filename);
  printf("[+]Closing the connection.\n");
  close(sockfd);

  return (0);
}


void ft_write_file(int sockfd){
  int n;
  FILE *fp;
  char *filename;
  printf("Write the file name\n");
  filename = get_next_line(0);
  filename[strcspn(filename, "\n")] = '\0';
  char buffer[SIZE];

  fp = fopen(filename, "w");
  if (!fp)
  {
    perror("[-]Error in opening file");
    return;
  }
  free(filename);
  while (1)
  {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0)
      break;
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  fclose(fp);
  return;
}

int ft_server(void)
{
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
  {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0)
  {
    perror("[-]Error in bind");
    exit(1);
  }
  printf("[+]Binding successfull.\n");

  if(listen(sockfd, 10) == 0)
    printf("[+]Listening....\n");
  else
  {
    perror("[-]Error in listening");
    exit(1);
  }

  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  ft_write_file(new_sock);
  printf("[+]Data written in the file successfully.\n");

  return (0);
}