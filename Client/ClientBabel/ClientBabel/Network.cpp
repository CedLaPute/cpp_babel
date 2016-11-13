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
      emit sig(QString("sds"));
      SocketManager manager("192.168.0.37", (short)2727);
      
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

void		Network::rcvName(QString const &s)
{
  std::cout << "dffeudnfusidbvuesdihbkvsdjkn" << std::endl;
  std::cout << s.toStdString() << std::endl;
}
