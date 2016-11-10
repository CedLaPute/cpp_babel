#include "../Headers/ASocket.hh"
# include <iostream>

#ifdef _WIN32
#include "../../Windows/Headers/WinSocket.hh"

#elif __linux__
#include "../../Unix/Headers/LinSocket.hh"
#endif

int	main(int , char **)
{
	ASocket *tmp;

	tmp = ASocket::getNewSocket(2727);
 	tmp->Connect("10.14.58.135", 2727);

	while (1)
	{
		tmp->Loop();
	}
  return 0;
}
