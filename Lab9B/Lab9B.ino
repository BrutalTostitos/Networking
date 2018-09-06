// Josh Wynn
// ETEC3201.01
// Lab 9b
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

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
      printf("Error when creating the socket\n");
      return(-1);
   }
   printf("Created socket\n");

   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(SEVPORT);

   if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == 0)
   {
      printf("Binded socket\n");
   }
   else
   {
      printf("Error occured when binding socket\n");
      return(-1);
   }


   while (1) {
      if (listen(sockfd, 10) < 0)
      {
         printf("Failed to listen on port\n");
         return(-1);
      }

      if ((acceptedfd = accept(sockfd, (struct sockaddr *) &address, &addrlen)) < 0)
      {
         printf("Failed to accept connection\n");
         return(-1);
      }


      if (acceptedfd > 0)
      {
         printf("Connected to client\n");
      }

      recv(acceptedfd, buffer, bufsize, 0);
      printf("%s\n", buffer);

      char tmp[2048];
      sprintf(tmp, "<html><body><p><pre>%s</pre></p></body></html>", buffer);
      printf(tmp);
      write(acceptedfd, "HTTP/1.1 200 OK\n", 16);

      write(acceptedfd, "Content-Type: text/html\n\n", 25);
      write(acceptedfd, tmp, strlen(tmp));

      close(acceptedfd);
   }
   close(sockfd);
   return 0;
}


