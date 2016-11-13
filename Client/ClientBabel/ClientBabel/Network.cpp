#include "Network.h"
#include "SocketManager.hh"
#include <iostream>

Network::Network()
{
  moveToThread(this);
}

void	Network::run()
{

  emit nameTaken();
  exec();
  try
    {
      SocketManager manager("10.45.14.249", (short)2727);
      
      while (manager.Select() != -1)
	{
	  manager.handleSend();
	  manager.handleReceive();
	}
      std::cout << "out" << std::endl;
    }
  catch (std::string const &err)
    {
      std::cerr << err << std::endl;
    }
}

void		Network::newName(QString const &s)
{
  std::cout << s.toStdString() << std::endl;
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
