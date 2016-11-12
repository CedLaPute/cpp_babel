#include "Network.h"
#include "SocketManager.hh"
#include <iostream>

Network::Network()
{
  setParent(0);
  moveToThread(this);
}

void	Network::run()
{
  try
    {
      SocketManager manager("192.168.1.91", (short)2727);
      
      while (manager.Select() != -1)
	{
		manager.handleSend();
	  manager.handleReceive();
	}
    }
  catch (std::string const &err)
    {
      std::cerr << err << std::endl;
    }
}
