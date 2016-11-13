#include "Network.h"
#include "SocketManager.hh"
#include <iostream>

Network::Network()
{
  moveToThread(this);
}

void	Network::run()
{
  try
    {
      SocketManager manager("192.168.1.91", (short)2728);
      
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

void		Network::newName(QString const &)
{

}

void		Network::sndCall(QString const &)
{

}

void		Network::acceptCall()
{

}

void		Network::refuseCall()
{

}

void		Network::endCall()
{

}
