#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "com.h"
#include "client.h"


void client()
{
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        perror("create socket fail");
        return;
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ret = connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    if (ret < 0) {
        perror("connct fail");
        return;
    }

    char buff[1024];
    int len = recv(sock, buff, sizeof(buff), 0);
    if (len < 0) {
        perror("recv fail");
        return;
    }
    printf("%s: %d\n", buff, len);

}