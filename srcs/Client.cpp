#include "Client.hpp"

Client::Client(unsigned int port) : _port(port), _socket(-1) {
  if (port == 0) throw std::runtime_error("Error: port error.");
  memset(&_buff, 0, BUF_SIZE);
  memset(&_serv_addr, '0', sizeof(_serv_addr));

  _serv_addr.sin_family = AF_INET;
  _serv_addr.sin_port = htons(_port);

  if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) throw std::runtime_error("Error: create socket failed.");
}

const unsigned int& Client::getPort(void) const { return _port; }
const char*         Client::getBuff(void) const { return _buff; }

bool  Client::connection(const char* address) {
  std::string addr(address);
  if (addr == "localhost") addr = "127.0.0.1";
  if (inet_pton(AF_INET, addr.c_str(), &(_serv_addr.sin_addr)) <= 0) {
    std::cerr << "Connection Error: address not supported." << std::endl;
    return false;
  }
  if (connect(_socket, (struct sockaddr*)&_serv_addr, sizeof(_serv_addr)) < 0) {
    std::cerr << "Connection Error: connection error." << std::endl;
    return false;
  }
  return true;
}

const std::string transMessage(const std::string& msg) {
  if (msg == "case 1") {
    return "GET / HTTP/1.1\r\n\r\n\r\n";
  } else if (msg == "case 2") {
    return "GET / HTTP/1.1\r\nHost: www.example.com\r\nConnection: keep-alive\r\n\r\n";
  }
  std::string changeMessage(msg);
  size_t      idx;
  while ((idx = changeMessage.find("\\r\\n")) != std::string::npos) {
    changeMessage.replace(idx, 4, "\r\n");
  }
  return changeMessage;
}

int  Client::sendRequest(const std::string& msg) {
  int n;

  const std::string message = transMessage(msg);

  send(_socket, message.c_str(), message.size(), 0);
  std::cout << "Sent message : " << message << std::endl;

  n = read(_socket, _buff, BUF_SIZE);
  std::cout << "received char : " << n << std::endl;
  return n;
}