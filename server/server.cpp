#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "com.h"
#include "server.h"
//using namespace std;

void server()
{
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        perror("create socket failed");
        return;
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("127.0.0.1")
    int ret = bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    if (ret < 0) {
        perror("bind socket failed");
        return;
    }

    ret = listen(sock, 5);
    if (ret < 0) {
        perror("listen socket failed");
        return;
    }

    struct sockaddr_in client_addr = {0};
    socklen_t len;

    std::vector<int> clients;
    while (true) {
        fd_set read_set;
        fd_set write_set;
        fd_set excp_set;

        FD_ZERO(&read_set);
        FD_ZERO(&write_set);
        FD_ZERO(&excp_set);

        FD_SET(sock, &read_set);
        FD_SET(sock, &write_set);
        FD_SET(sock, &excp_set);

        for (auto s : clients) {
            FD_SET(s, &read_set);
        }

        struct timeval tv = {5, 0};
        int ret = select(sock + 1, &read_set, &write_set, &excp_set, &tv);
        if (ret < 0) {
            perror("select error");
            continue;
        }

        if (FD_ISSET(sock, &read_set)) {
            int client = accept(sock, (struct sockaddr *)&client_addr, &len);
            if (client < 0) {
                perror("accept socket failed");
                return; 
            }

            printf("New Client: %s\n", inet_ntoa(client_addr.sin_addr));

            clients.push_back(client);
            continue;
        }

        for (auto i : clients) {
            if (FD_ISSET(i, &read_set)) {
                const char * buff= "Hello Server";
                send(i, buff, strlen(buff) + 1, 0);
            }
        }
    }
}