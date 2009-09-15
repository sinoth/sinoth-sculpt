
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

#ifdef _WIN32
 #include <ws2tcpip.h>
 //these functions not present on windows, must use wrappers
 const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
 int inet_pton(int af, const char *src, void *dst);
#else
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <netdb.h>
 #include <arpa/inet.h>
 #include <sys/wait.h>
#endif

#include "sinsocket.h"


bool sinsocket::done_init = false;
int sinsocket::socket_count = 0;

///////////////////////////////////////////////////////////////////////////////
//
sinsocket::sinsocket(int in_fd) : ready_for_action(false), my_socket(in_fd) {

    if ( in_fd != -1 ) ready_for_action = true;

    if ( !done_init ) {
        printf("sinsocket: init\n");
        #ifdef _WIN32_WINNT
        WSADATA wsaData;   // if this doesn't work try WSAData
        // MAKEWORD(1,1) for Winsock 1.1, MAKEWORD(2,0) for Winsock 2.0:
        if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0) {
            fprintf(stderr, "sinsocket: listen: WSAStartup failed.\n");
            WSACleanup();
            exit(1); }
        #endif

        done_init = true;
    }

    socket_count++;
}


///////////////////////////////////////////////////////////////////////////////
//
sinsocket::~sinsocket() {

    //if this guy is the last socket, go ahead and uninit
    if ( socket_count == 1 && done_init ) {
        printf("sinsocket: uninit\n");
        #ifdef _WIN32_WINNT
        WSACleanup();
        #endif

        done_init = false;
    }

    socket_count--;
}


///////////////////////////////////////////////////////////////////////////////
//
int sinsocket::listen(int in_port) {

    struct addrinfo hints, *servinfo, *p;
    char yes=1;
    int return_value;

    sprintf(my_port,"%d",in_port);


    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((return_value = getaddrinfo(NULL, my_port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "sinsocket: listen: getaddrinfo: %s\n", gai_strerror(return_value));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((my_socket = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("socket");
            continue;
        }

        if (setsockopt(my_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(char)) == -1) {
            perror("setsockopt");
            continue;
        }

        if (bind(my_socket, p->ai_addr, p->ai_addrlen) == -1) {
            close(my_socket);
            perror("bind");
            continue;
        }

        break;
    }

    if (p == NULL)  {
        fprintf(stderr, "sinsocket: listen: failed to bind\n");
        return 1;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (::listen(my_socket, 10) == -1) { //this value is the 'backlog'
        perror("listen");
        return 1;
    }

    ready_for_action = true;
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
sinsocket* sinsocket::accept() {

    int new_fd;  // listen on sock_fd, new connection on new_fd
    struct sockaddr_storage their_addr; // connector's address information
    char connection_name[INET6_ADDRSTRLEN];
    socklen_t sin_size;

    printf("sinsocket: accept: waiting for connections...\n");

    sin_size = sizeof their_addr;
    new_fd = ::accept(my_socket, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == -1) {
        perror("accept");
        return NULL; }

    inet_ntop(their_addr.ss_family,
              get_in_addr((struct sockaddr *)&their_addr),
              connection_name,
              sizeof connection_name);
    printf("sinsocket: accept: got connection from %s\n", connection_name);

    return new sinsocket(new_fd);

}


///////////////////////////////////////////////////////////////////////////////
//
int sinsocket::send( const void *indata, int inlength ) {
    int bytes_sent = 0;
    int bytes_left = inlength;
    int temp_sent = 0;

    while ( bytes_sent < inlength ) {
        temp_sent = ::send(my_socket, (const char*)indata+bytes_sent, bytes_left, 0);
        if ( temp_sent == -1 ) break; //something bad happened
        bytes_sent += temp_sent;
        bytes_left -= temp_sent;
    }

    if ( temp_sent == -1 ) { perror("send"); }

    //return 1 if something messed up, 0 otherwise
    return ( temp_sent==-1?1:0 );
}


///////////////////////////////////////////////////////////////////////////////
//
int sinsocket::recv( const void *inbuffer, int inlength ) {
    int bytes_recv = 0;
    int bytes_left = inlength;
    int temp_recv = 0;

    while ( bytes_recv < inlength ) {
        temp_recv = ::send(my_socket, (const char*)inbuffer+bytes_recv, bytes_left, 0);
        if ( temp_recv == -1 || temp_recv == 0 ) break; //something bad happened or disconnect
        bytes_recv += temp_recv;
        bytes_left -= temp_recv;
    }


    //error
    if ( temp_recv == -1 ) { perror("recv"); }
    //peer disconnected
    if ( temp_recv == 0 ) {
        fprintf(stderr, "sinsocket: recv: peer has disconnected\n");
        ready_for_action = false; }

    //return 1 if the peer disconnected, -1 for error, 0 otherwise
    return temp_recv;
}


///////////////////////////////////////////////////////////////////////////////
//
int sinsocket::connect(const char* inaddress, int inport ) {

    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure




}

///////////////////////////////////////////////////////////////////////////////
//
void *sinsocket::get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) //IPv4
      return &(((struct sockaddr_in*)sa)->sin_addr);
    else //IPv6
      return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

