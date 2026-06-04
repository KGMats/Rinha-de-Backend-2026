// #include "network.hpp"
#include "kmeanspp.hpp"
#include "cluster.hpp"
#include "kmknn.hpp"
#include "vector.hpp"
#include "network.hpp"
#include "vector.hpp"
#include "cluster.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>


#define CLUSTERS_INDEX_FILE "clusters_index.bin"
#define NNEIGHBORS 5

Cluster* clusters;
bool built = false;

int main()
{
    ifstream file("../docs/miniref.json");
    if (!file)
    {
        cerr << "Failled to open references file, Aborting.";
        exit(1);
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    const char* json_dict = content.c_str();


    Vector* data = references_parser(json_dict);

    clusters = (Cluster*)malloc(sizeof(Cluster) * SQRT_NVECTORS);

    ifstream bin_file(CLUSTERS_INDEX_FILE, ios::binary);
    if (bin_file)
    {
        cout << "Loading clusters from " << CLUSTERS_INDEX_FILE << "..." << endl;
        bin_file.read((char*)clusters, sizeof(Cluster) * SQRT_NVECTORS);
        bin_file.close();
        built = true;
    }
    else
    {
        cout << "Calculating clusters (this may take a while)..." << endl;
        Cluster* calculated_clusters = kmeanspp(SQRT_NVECTORS, data);
        memcpy(clusters, calculated_clusters, sizeof(Cluster) * SQRT_NVECTORS);
        free(calculated_clusters);

        ofstream out_file(CLUSTERS_INDEX_FILE, ios::binary);
        if (out_file)
        {
            out_file.write((char*)clusters, sizeof(Cluster) * SQRT_NVECTORS);
            out_file.close();
            cout << "Clusters saved to " << CLUSTERS_INDEX_FILE << endl;
        }
        built = true;
    }

    for (int i = 0; i < SQRT_NVECTORS; i++)
    {
        if (clusters[i].size > 0)
            cout << clusters[i].size << ',';
    }
    cout << endl;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    char buffer[512];

    if (server_fd < 0)
    {
        perror("socket");
        return -1;
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
        return -1;
    }

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, CONNECTION_QUEUE_SIZE) < 0)
    {
        perror("listen");
        close(server_fd);
        return -1;
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
        Vector data_vec = parse_request(ptr);
        // ENDPOINT /fraud-score

        Vector **neighbors = KMKNN::kmppknn(data_vec, NNEIGHBORS, clusters, data);

        int counter = 0;
        for (int i = 0; i < NNEIGHBORS; i++)
        {
            counter += neighbors[i]->label == 'f';
        }


        write(client_fd, responses[counter], response_sizes[counter]);
        close(client_fd);
    }



    return 0;
}
