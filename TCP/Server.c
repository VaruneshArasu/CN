#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
void func(int sockfd);
int main() {
    int sockfd;
    struct sockaddr_in servaddr;
 // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("\nSocket creation failed\n");
        return -1;
    } else {
        printf("\nSocket created successfully\n");
    }
// Server details
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(43451); // Port number
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost IP
 // Connect to server
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        printf("\nConnection to server failed\n");
        return -1;
    } else {
        printf("\nConnected to server successfully\n");
        func(sockfd); // Handle the communication with the server
    }
// Close the socket after communication is done
    close(sockfd);
    return 0;
}

void func(int sockfd) {
    int msg;
// Send and receive the values p, n, r, and interest
    printf("\nEnter the value for p: ");
    scanf("%d", &msg);
    write(sockfd, &msg, sizeof(msg));
   printf("\nEnter the value for n: ");
    scanf("%d", &msg);
    write(sockfd, &msg, sizeof(msg));
    printf("\nEnter the value for r: ");
    scanf("%d", &msg);
    write(sockfd, &msg, sizeof(msg));
   // Receive interest from the server
    printf("\nInterest amount is: ");
    read(sockfd, &msg, sizeof(msg));
    printf("%d\n", msg);
}
