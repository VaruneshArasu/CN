#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
// Function declaration
void func(int sockfd);
int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
  // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("\nSocket creation failed\n");
        return 1;
    }
    else
    {
        printf("\nSocket is created\n");
     // Set server information
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(43451); // Port number
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost IP
// Connect to the server
        if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
        {
            printf("\nConnection failed\n");
            close(sockfd);
            return 1;
        }
        else
        {
            printf("\nServer accepted successfully\n");
// Call the function to communicate with the server
            func(sockfd);
 // Close the socket after communication is done
            close(sockfd);
        }
    }
    return 0;
}

void func(int sockfd)
{
    char client_msg[10], server_msg[10];
 // Get input from the client
    printf("\nClient: ");
    scanf("%s", client_msg);
 // Send the message to the server
    write(sockfd, client_msg, strlen(client_msg));
// Receive the message from the server
    read(sockfd, server_msg, sizeof(server_msg));
    // Print the server's response
    printf("Server: %s\n", server_msg);
}

