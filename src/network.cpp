#include "network.hpp"
#include "vector.hpp"

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>


static const char *responses[7] = {
    "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 35\r\n\r\n{\"approved\":true,\"fraud_score\":0.0}\r\n\r\n",
    "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 35\r\n\r\n{\"approved\":true,\"fraud_score\":0.2}\r\n\r\n",
    "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 35\r\n\r\n{\"approved\":true,\"fraud_score\":0.4}\r\n\r\n",
    "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 36\r\n\r\n{\"approved\":false,\"fraud_score\":0.6}\r\n\r\n",
    "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 36\r\n\r\n{\"approved\":false,\"fraud_score\":0.8}\r\n\r\n",
    "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 36\r\n\r\n{\"approved\":false,\"fraud_score\":1.0}\r\n\r\n",
    "HTTP/1.1 200 OK\r\nContent-Length: 0\r\nConnection: close\r\n\r\n",
};


static const char response_sizes[] = {
    sizeof("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 35\r\n\r\n{\"approved\":true,\"fraud_score\":0.0}\r\n\r\n"),
    sizeof("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 35\r\n\r\n{\"approved\":true,\"fraud_score\":0.2}\r\n\r\n"),
    sizeof("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 35\r\n\r\n{\"approved\":true,\"fraud_score\":0.4}\r\n\r\n"),
    sizeof("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 36\r\n\r\n{\"approved\":false,\"fraud_score\":0.6}\r\n\r\n"),
    sizeof("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 36\r\n\r\n{\"approved\":false,\"fraud_score\":0.8}\r\n\r\n"),
    sizeof("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 36\r\n\r\n{\"approved\":false,\"fraud_score\":1.0}\r\n\r\n"),
    sizeof("HTTP/1.1 200 OK\r\nContent-Length: 0\r\nConnection: close\r\n\r\n"),
};

void serve()
{
    int server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    char buffer[512];

    if (server_fd < 0)
    {
        perror("socket");
        return;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(LISTENING_PORT);


    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt SO_REUSEADDR");
        close(server_fd);
        return;
    }

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        close(server_fd);
        return;
    }

    if (listen(server_fd, CONNECTION_QUEUE_SIZE) < 0)
    {
        perror("listen");
        close(server_fd);
        return;
    }

    for (;;)
    {
        struct sockaddr_in client_addr;
        socklen_t client_size = sizeof(client_addr);

        int client_fd = accept(
                server_fd,
                (struct sockaddr*)&client_addr,
                &client_size
                );

        if (client_fd < 0)
            continue;


        // ========== process request ========== //
        size_t msg_size = read(client_fd, buffer, 512);

        buffer[msg_size] = '\0'; // End string



        // We only need the fist char - G or P in case of GET or POST method,
        // respectively - to determine if we do need to handle vector search
        // or /ready endpoint


        // ENDPOINT /ready
        if (buffer[0] == 'G')
        {
            // TODO: Return 200 only after processing KMNN
            

            write(client_fd, responses[6], response_sizes[6]);
            close(client_fd);
            continue;
        }

        const char *ptr = buffer;
        Vector data = parse_request(ptr);
        // ENDPOINT /fraud-score
        write(client_fd, responses[1], response_sizes[1]);
        close(client_fd);


        continue;
    }
}
