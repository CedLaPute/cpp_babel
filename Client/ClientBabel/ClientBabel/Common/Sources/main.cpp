#include "../Headers/ASocket.hh"
# include <iostream>

#ifdef _WIN32
 #include "../../Windows/Headers/WinSocket.hh"

#elif __linux__

 #include "../../Unix/Headers/LinSocket.hh"

#endif

int main(int, char **av)
{
  ASocket *tmp;
  char *str;
  tmp = ASocket::getNewSocket((short) atoi(av[2]));
  tmp->Connect(av[1], (short) atoi(av[2]));
  str = tmp->Receive();
  std::cout << Buffer::getValue(str)->data << "--" << std::endl;
  return 0;
}
