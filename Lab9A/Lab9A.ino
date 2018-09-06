// Josh Wynn
// ETEC3201.01
// Lab 9A
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

#define SEVPORT 5678

int main() {
   int sockfd, acceptedfd;
   socklen_t addrlen;
   int bufsize = 1024;
   char *buffer = malloc(bufsize);
   struct sockaddr_in address;

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
   {
      printf("Error while trying to create the socket\n");
      return(-1);
   }
   printf("Created socket successfully\n");

   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(SEVPORT);

   if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == 0)
   {
      printf("Socket binded successfully\n");
   }
   else
   {
      printf("Error when binding the socket\n");
   }

   while (1) {
      if (listen(sockfd, 10) < 0) {
         printf("Error while trying to listen\n");
         return(-1);
      }

      if ((acceptedfd = accept(sockfd, (struct sockaddr *) &address, &addrlen)) < 0) {
         printf("There was an error accepting the client\n");
         return(-1);
      }

      if (acceptedfd > 0){
         printf("The Client is connected\n");
      }
      else
      {
         printf("There was an error when connecting to the client\n");
         return(-1);
      }

      recv(acceptedfd, buffer, bufsize, 0);
      printf("%s\n", buffer);
      write(acceptedfd, "HTTP/1.1 200 OK\n", 16);
      write(acceptedfd, "Content-length: 46\n", 19);
      write(acceptedfd, "Content-Type: text/html\n\n", 25);
      write(acceptedfd, "<html><body><center><p>William Buell</p></center></body></html>",46);
      close(acceptedfd);
   }
   close(sockfd);
   return 0;
}                                                                                                                                                                                                                                                                                           30,5          All

