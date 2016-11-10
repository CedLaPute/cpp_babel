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

  tmp = ASocket::getNewSocket((short) atoi(av[2]));
  tmp->Connect(av[1], (short) atoi(av[2]));
  tmp->Receive();
  sleep(5);
  return 0;
}
