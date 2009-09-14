
class sinsocket {
public:

    //to know if the program-wide init has been run
    static bool done_init;


    //server functions
    int listen(int port);
    //int listen(int port, int sockets_per_thread);
    //int listen(int port, int sockets_per_thread, int threads );
    sinsocket* accept();

    //client functions
    int connect(const char* address, int port);


    sinsocket();


private:

    int my_socket;


};



//this class allows you to say, initialize 10 sockets and listen to all simultaneously
//it also allows them to be serviced simultaneously
class sinsocket_farm {
public:



private:

}
