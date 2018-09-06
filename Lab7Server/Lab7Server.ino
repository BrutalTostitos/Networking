// Josh Wynn
// ETEC3201.01
// Lab 7 - Server
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define SERVPORT 3456

main()
{
  int sockfd,newfd;
  int bytes_recv=0;
  int err;
  char buffer[8192];
  struct sockaddr_in my_addr;
  struct sockaddr_in their_addr;
  int their_addr_size=16;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    printf("Unable to open socket.\n");
    return(-1);
  }
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons( SERVPORT );
  my_addr.sin_addr.s_addr = 0;
  bzero( &(my_addr.sin_zero),8 );

  err = bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr));
  if (err == -1)
  {
    printf("Unable to bind port.\n");
    return(-1);
  }


  err = listen(sockfd,10);
  if (err == -1)
  {
    printf("Failed to listen to socket.\n");
    return(-1);
  }
  newfd=accept(sockfd,&their_addr,&their_addr_size);
  if (newfd == -1)
  {
    printf("Failed to accept connection.\n");
    return(-1);
  }
  bytes_recv=recv(newfd,buffer,8192,0);
  if (bytes_recv == -1)
  {
    printf("Failed to receive.\n");
    return(-1);
  }
  printf("Line recvd: %s\n",buffer);

  printf("\n\nClosing...");
  err = shutdown(sockfd, 2);
  if (err == -1)
  {
    printf("Failed to shutdown.\n");
    return(-1);
  }
  printf("\n\nClosed!\n");

}
