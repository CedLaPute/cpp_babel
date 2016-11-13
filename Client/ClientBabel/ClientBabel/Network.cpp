#include "Network.h"
#include <iostream>

Network::Network()
{
  moveToThread(this);
}

void	Network::run()
{
  this->_loop = new QEventLoop();
  this->_timer = new QTimer();

  this->_timer->setSingleShot(true);
  connect(this->_timer, SIGNAL(timeout()), this->_loop, SLOT(quit()));
  
  this->_sm = new SocketManager("10.14.58.135", (short)2728);
  try
    {      
      while (this->_sm->Select() != -1)
    	{
        this->_timer->start(0);
    	  this->_sm->handleSend();
    	  this->_sm->handleReceive();
        this->_loop->exec();
    	}
    }
  catch (std::string const &err)
    {
      std::cerr << err << std::endl;
    }
}

void		Network::newName(QString const &s)
{
  this->_sm->setName(s.toStdString());
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
