#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = { 0 };
    const char* message = "客户端消息：Hello from client";

    // 创建socket文件描述符
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket创建错误 \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 将IPv4和IPv6地址从文本转换为二进制形式
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n无效地址/地址不支持 \n");
        return -1;
    }

    // 连接到服务器
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n连接失败 \n");
        return -1;
    }

    // 发送数据到服务器
    send(sock, message, strlen(message), 0);
    printf("客户端问候消息已发送\n");

    // 读取服务器响应
    read(sock, buffer, BUFFER_SIZE);
    printf("来自服务器的消息：%s\n", buffer);

    // 关闭socket
    close(sock);
    return 0;
}