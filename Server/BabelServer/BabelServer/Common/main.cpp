#ifdef _WIN32
 # include "../Windows/WinSocket.hh"
#elif __linux__

 # include "../Unix/LinSocket.hh"

#endif

# include "ASocket.hh"
# include "SocketManager.hh"
# include "UserManager.hh"
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
  ASocket *newConnection;
  UserManager um;

  while (sm.Select() != -1)
  {
	um.handleSend(sm);
	um.handleReceive(sm);
	um.handlePendingAuth(sm);
	newConnection = sm.tryNewConnection();
	if (newConnection)
	{
	  um.addUser("", newConnection);
	  um.addPendingAuth(newConnection);
	  newConnection = NULL;
	}
  }
  return (0);
}
