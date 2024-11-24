#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
void func(int confd);
int main() {
    int sockfd, len, confd;
    struct sockaddr_in servaddr, cliaddr;
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        return -1;
    } else {
        printf("\nSocket created successfully\n");
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(43451);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
   if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        printf("\nBind failed\n");
        return -1;
    } else {
        printf("\nBind successful\n");
    }
   if (listen(sockfd, 5) == -1) {
        printf("\nListen failed\n");
        return -1;
    } else {
        printf("\nListening for connections\n");
    }

   
    len = sizeof(cliaddr);
    confd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if (confd == -1) {
        printf("\nAccept failed\n");
        return -1;
    } else {
        printf("\nClient accepted successfully\n");
        func(confd); 
    }
    close(confd);
    close(sockfd);
    return 0;
}
void func(int confd) {
    int si, msg, tot;
   printf("\nThe value for p:\n");
    read(confd, &msg, sizeof(msg)); 
    printf("%d\n", msg);
    si = msg;  
    printf("\nThe value for n:\n");
    read(confd, &msg, sizeof(msg)); 
    printf("%d\n", msg);
    si = msg * si; 
    printf("\nThe value for r:\n");
    read(confd, &msg, sizeof(msg)); 
    printf("%d\n", msg);
    si = msg * si;  
    tot = si / 100;
    printf("\nThe total interest amount is: %d\n", tot);
    write(confd, &tot, sizeof(tot));
}
