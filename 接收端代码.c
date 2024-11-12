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
    const char* message = "�ͻ�����Ϣ��Hello from client";

    // ����socket�ļ�������
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket�������� \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // ��IPv4��IPv6��ַ���ı�ת��Ϊ��������ʽ
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n��Ч��ַ/��ַ��֧�� \n");
        return -1;
    }

    // ���ӵ�������
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n����ʧ�� \n");
        return -1;
    }

    // �������ݵ�������
    send(sock, message, strlen(message), 0);
    printf("�ͻ����ʺ���Ϣ�ѷ���\n");

    // ��ȡ��������Ӧ
    read(sock, buffer, BUFFER_SIZE);
    printf("���Է���������Ϣ��%s\n", buffer);

    // �ر�socket
    close(sock);
    return 0;
}