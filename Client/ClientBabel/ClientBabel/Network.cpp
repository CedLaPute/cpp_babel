#include "Network.hh"
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
      SocketManager manager("10.14.60.27", (short)2727);
      
      while (manager.Select() != -1)
	{
	  manager.handleReceive();
	}
    }
  catch (std::string const &err)
    {
      std::cerr << err << std::endl;
    }
  
  emit sig(QString("lelelelele"));
}
