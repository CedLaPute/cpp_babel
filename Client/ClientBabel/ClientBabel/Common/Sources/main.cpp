#include "../ASocket.hh"

#ifdef _WIN32
#include "../../Windows/WinSocket.hh"

#elif __linux__
#include <LinNetwork.hh>
#endif

int	main(int , char **)
{
	ASocket *tmp;
  
	tmp = ASocket::getNewSocket(2728);
 	tmp->Connect("10.14.58.115", 2728);

  while (1)
    {
      tmp->Loop();
    }
  return 0;
}
