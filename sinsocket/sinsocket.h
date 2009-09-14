
class sinsocket {
public:

    //server functions
    int listen(int port); //eventually add sockets_per_thread and threads inits
    sinsocket* accept();

    //client functions
    int connect(const char* address, int port);

    //shared functions
    int send
    int recv

    sinsocket(int my_sockd=-1);
    ~sinsocket();


private:

    bool ready_for_action;
    int my_socket;
    char my_port[6];
    void *get_in_addr(struct sockaddr *sa);

    //to know if the program-wide init has been run
    static bool done_init;
    static int socket_count;

};



//this class allows you to service multiple sockets simultaneously in one thread
class sinsocket_farm {
public:
private:
};
