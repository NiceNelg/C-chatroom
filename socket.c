#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include "socket.h"

#define QUEUE 20
#define BUFFER_SIZE 1024

int socket_build(char *address, char *port_s) 
{
    int port = atoi((const char *)port_s);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_socketaddr;
    server_socketaddr.sin_family = AF_INET;
    server_socketaddr.sin_port = htons(port);
    server_socketaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(fd, (struct sockaddr *)&server_socketaddr, sizeof(server_socketaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    printf("监听%d端口\n", port);

    if(listen(fd, QUEUE) == -1) {
        perror("listen error");
        exit(1);
    }

    char buffer[BUFFER_SIZE];

    struct sockaddr_in client_addr;

    socklen_t length = sizeof(client_addr);
    printf("等待客户端连接\n");

    int conn = accept(fd, (struct sockaddr *)&client_addr, &length);

    if(conn < 0) {
        perror("connect error\n");
        exit(0);
    }
    printf("客户端连接成功\n");

    while(1) {
        memset(buffer, 0, sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer), 0);
        
        if(strcmp(buffer, "exit\n") == 0 || len <= 0) {
            break;
        }    

        printf("来自客户端数据：%s\n", buffer);
        send(conn, buffer, len, 0);
        printf("发送给客户端数据：%s\n", buffer);
    }
    close(conn);
    close(fd);
    return 0;
}
