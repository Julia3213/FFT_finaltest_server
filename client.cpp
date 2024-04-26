#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

constexpr int PORT = 8080;
constexpr char* SERVER_IP = "127.0.0.1";
constexpr int BUFFER_SIZE = 1024;

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = { 0 };
    const char* message = "Hello from client";

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }

    send(sock, message, strlen(message), 0);
    std::cout << "Message sent to server" << std::endl;

    valread = read(sock, buffer, BUFFER_SIZE);
    std::cout << "Received ACK from server: " << buffer << std::endl;

    return 0;
}
