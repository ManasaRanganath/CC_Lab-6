#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nServed by backend: " + std::string(hostname) + "\n";
    
    while(true) {
        int new_socket = accept(server_fd, NULL, NULL);
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);
        send(new_socket, response.c_str(), response.length(), 0);
        close(new_socket);
    }
    return 0;
}