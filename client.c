#include "client.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int client(const char* ip, unsigned short port);
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    bzero(&(server_addr.sin_zero), 8);
    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
    return sockfd;