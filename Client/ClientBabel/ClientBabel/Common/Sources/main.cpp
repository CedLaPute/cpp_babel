#include "../ASocket.hh"

#ifdef _WIN32
#include "../../Windows/WinSocket.hh"

#elif __linux__
#include <LinNetwork.hh>
#endif

int	main(int , char **)
{
	ASocket *tmp;


  #ifdef _WIN32
	tmp = ASocket::getNewSocket(2727);
  #elif __linux__
    LinNetwork *tmp = new LinNetwork;
  #endif

  tmp->Connect("10.14.58.115", 2727);

  while (1)
    {
      tmp->Loop();
    }
  return 0;
}
