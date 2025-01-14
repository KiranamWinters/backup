#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SUCCESS 0


int main(int argc, char** argv){
        struct addrinfo hints;
        struct addrinfo *res;
        char address[INET_ADDRSTRLEN];

        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        int status = getaddrinfo(argv[1], NULL, &hints, &res);
        if(status != SUCCESS){
                printf("Error: %s\n", gai_strerror(status));
                return 2;
        }

        struct sockaddr_in *info = (struct sockaddr_in*)res->ai_addr;
        if(inet_ntop(res->ai_family, &info->sin_addr, address, sizeof(address)) != SUCCESS){
                printf("Error\n");
                return 3;
        }

        printf("address: %s\n", address);
}
