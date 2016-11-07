#ifdef _WIN32
 # include "../Windows/WinSocket.hh"
#elif __linux__

 # include "../Unix/LinSocket.hh"

#endif

# include "ASocket.hh"
# include "SocketManager.hh"
# include <iostream>
# include <vector>

int main(int ac, char **av)
{
  if (ac != 2)
  {
	std::cout << "usage: ./babel_server port" << std::endl;
	return (0);
  }
  SocketManager sm((short) atoi(av[1]));
  int i = -1;

  while (++i < 5)
	sm.Select();

//	try
//	{
//		std::vector<ASocket *>	_sockets; // TEST
//
//		ASocket *absSocket = ASocket::getNewSocket(4);
//
//		if (absSocket == NULL)
//			throw "getSocket failed";
//
//		printf("getSocket ok\n");
//
//		absSocket->Listen();
//		_sockets.push_back(absSocket);
//	}
//	catch (const std::string &err)
//	{
//		std::cerr << err << std::endl;
//	}

  return (0);
}
