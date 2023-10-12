#include "Client.hpp"

int main(int ac, char* av[]) {
  if (ac != 4) {
    std::cerr << "invalid arguments.\n" << "./client [address] [port] [massage]" << std::endl;
    return 1;
  }
  try {
    int     n = 0;
    Client  cli(atoi(av[2]));

    cli.connection(av[1]);

    n = cli.sendRequest(std::string(av[3]));
    if (n) {
      const char* buff = cli.getBuff();
      std::cout << "received message:\n----------\n" << std::endl;
      for (int i = 0;i < n; ++i) { std::cout << buff[i]; }
      std::cout<< "\n----------" << std::endl;
    }
  } catch (std::exception& e) { std::cerr << e.what() << std::endl; }
  return 0;
}