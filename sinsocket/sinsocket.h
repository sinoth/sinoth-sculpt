
class sinsocket {
public:

    //to know if the program-wide init has been run
    static bool done_init;


    //server functions
    int listen(int port);
    int listen(int port, int threads);
    int listen(int port, int threads, int sockets_per_thread);

    //client functions
    int connect(const char* address, int port);


    sinsocket();




};
