

#include "sinsocket.h"




int sinsocket::listen(int port) {

    int new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    //struct sigaction sa;
    char yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

#ifdef _WIN32_WINNT
    WSADATA wsaData;   // if this doesn't work try WSAData

    // MAKEWORD(1,1) for Winsock 1.1, MAKEWORD(2,0) for Winsock 2.0:
    if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        WSACleanup();
        exit(1);
    }
#endif

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((my_socket = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(my_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(char)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(my_socket, p->ai_addr, p->ai_addrlen) == -1) {
            close(my_socket);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        return 1;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (listen(my_socket, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    //while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(my_socket, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            #ifdef _WIN32_WINNT
            WSACleanup();
            #endif
            exit(1);
        }

}
