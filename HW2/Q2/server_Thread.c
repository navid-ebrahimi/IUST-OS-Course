#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>



// in your browser type: http://localhost:8090
// IF error: address in use then change the PORT number
#define PORT 8084

typedef struct 
{
    int new_socket;
} 
server;

void* myThreadFunc(void* arg)
{
    server *args = (server *) arg;
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	char buffer[30000] = {0};
    long valread = read( args -> new_socket , buffer, 30000);
    printf("%s\n",buffer );
    // uncomment following line and connect many clients
    sleep(1);
    write(args -> new_socket , hello , strlen(hello));
    printf("-------------Hello message sent---------------");
    close(args -> new_socket);
    // pthread_exit(NULL);
    return NULL;
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        pthread_t tid;
        server* thread_server = (server*)malloc(sizeof(server));
        thread_server -> new_socket = new_socket;
        pthread_create(&tid, NULL, myThreadFunc, thread_server);
    }
    return 0;
}