#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
// Function declaration
void func(int confd);
int main()
{
    int sockfd, confd, len;
    struct sockaddr_in servaddr, cliaddr;
 // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket creation failed\n");
return 1;
    }
    else
    {
        printf("\nSocket is created\n");
 // Set server information
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(43451); // Port number
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost IP
 // Bind the socket
        if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
        {
            printf("\nBind failed\n");
            close(sockfd);
            return 1;
        }
        else
        {
            printf("\nBind successfully\n");
// Listen for incoming connections
            if (listen(sockfd, 5) == -1)
            {
                printf("\nListen failed\n");
                close(sockfd);
                return 1;
            }
            else
            {
                printf("\nListening successfully\n");
// Accept an incoming connection
                len = sizeof(cliaddr);
                confd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
                if (confd == -1)
                {
                    printf("\nAccept failed\n");
                    close(sockfd);
                    return 1;
                }
                else
                {
                    printf("\nServer accepted client successfully\n");
  // Function to handle client-server communication
                    func(confd);
// Close the connection socket after communication
                    close(confd);
                }
            }
        }
    }
// Close the server socket
    close(sockfd);
    return 0;
}
// Function to handle communication with the client
void func(int confd)
{
    char client_msg[10], server_msg[10];
 // Read message from client
    read(confd, client_msg, sizeof(client_msg));
    printf("\nClient: %s\n", client_msg);
// Get message from server (user input)
    printf("\nServer: ");
    scanf("%s", server_msg);
  // Send server message to the client
    write(confd, server_msg, strlen(server_msg) + 1);
}
