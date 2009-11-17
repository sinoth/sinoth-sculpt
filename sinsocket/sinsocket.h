
#ifndef _SINSOCKET_H
#define _SINSOCKET_H

class sinsocket {
public:

    //server functions
    int listen(int port); //eventually add sockets_per_thread and threads inits
    sinsocket* accept();

    //client functions
    int connect(const char* address, int port);

    //shared functions
    int send( const void *data, int len ); //blocking
    int recv( const void *buf, int len ); //blocking
    int beginDisconnect();
    int endDisconnect();
    int closeSinsocket();

    sinsocket(int my_sockd=-1);
    ~sinsocket();

private:

    bool ready_for_action;
    int my_socket;
    char my_port[6];

    //buffer madness
    char recv_buffer[32768];
    int bytes_in_buffer;

    //to know if the program-wide init has been run
    static bool done_init;
    static int socket_count;

};



//this class allows you to service multiple sockets simultaneously in one thread
class sinsocket_farm {
public:
private:
};


#endif
