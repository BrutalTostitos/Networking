// Josh Wynn
// ETEC3201.01
// Lab 7 - Client

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define DESTPORT 3456

main()
{
  int sockfd;
  int bytes_sent;
  int retval;
  int err;
  char buffer[8192] = "Watson can you hear me?";

  struct sockaddr_in dest_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sockfd==-1)
  {
    printf("Unable to open the socket.\n");
    return(-1);
  }

  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons( DESTPORT );
  dest_addr.sin_addr.s_addr = inet_addr("192.168.7.2");
  bzero( &(dest_addr.sin_zero),8 );

  retval=connect(sockfd,(struct sockaddr *)&dest_addr,sizeof(struct sockaddr));
  if (retval == -1)
  {
    printf("Unable to connect.\n");
    return(-1);
  }
  printf("sending message: %s\n",buffer);
  bytes_sent=send(sockfd,buffer,strlen(buffer)+1,0);
  if (bytes_sent == -1)
  {
    printf("Message failed to send.\n");
    return(-1);
  }
  printf("bytes sent: %d\n",bytes_sent);

  printf("Closing...\n");
  err = shutdown(sockfd, 2);
  if (err == -1)
  {
    printf("Failed to shutdown.\n");
    return(-1);
  }
  printf("Closed!\n");

}
