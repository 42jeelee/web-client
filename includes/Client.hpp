#ifndef CLIENT_HPP_
# define CLIENT_HPP_

# include <sys/socket.h>
# include <stdlib.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <iostream>
# include <exception>


# define BUF_SIZE 4096

class Client {
  private:
    unsigned int        _port;
    int                 _socket;

    struct sockaddr_in  _serv_addr;

    char                _buff[BUF_SIZE];

    Client();
  public:
    Client(unsigned int port);

    const unsigned int& getPort(void) const;
    const char*         getBuff(void) const;

    bool  connection(const char* address);
    int   sendRequest(const std::string& msg);
};

#endif