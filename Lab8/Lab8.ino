// Josh Wynn
// ETEC3201.01
// Lab 8
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>

int main ( int argc, char *argv[] )
{
        int err;
        struct hostent * HostData;
        int i = 0;
        if (argc != 2)
        {
                printf("Please only pass one argument\n");
                printf("<program name> <website url>.\n");
                return(-1);
        }

        HostData = gethostbyname(argv[1]);
        if (HostData == -1)
        {
                printf("Failed to resolve hostname.\n");
                return(-1);
        }
        printf("Name of Host : %s\n", HostData->h_name);
        printf("Alias List :\n");

        char **pAlias;
        for (pAlias = HostData->h_aliases; *pAlias != 0; pAlias++)
        {
                printf("\t%s\n", *pAlias);
        }

        struct in_addr **pptr = (struct in_addr **)HostData->h_addr_list;
        printf("List of Addresses :\n");
        while (*pptr != NULL)
        {

                printf("\t%s\n", inet_ntoa(**(pptr++)));
        }
}
