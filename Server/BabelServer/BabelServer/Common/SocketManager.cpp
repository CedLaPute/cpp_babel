//
// Created by lemonti on 11/7/16.
//

#include <iostream>
#include "SocketManager.hh"

SocketManager::SocketManager(short port)
{
  this->_listener = ASocket::getNewSocket(port, "TCP");
  this->_listener->Bind();
  this->_listener->Listen();
}

SocketManager::~SocketManager()
{
}

void SocketManager::addSocket(ASocket *socket)
{
  this->_sockList.push_back(socket);
}

bool SocketManager::removeSocket()
{
  return (true);
}

unsigned int SocketManager::_fillFDSet(FDSetType set)
{
  unsigned int maxfd;
  unsigned int tmp;

  FD_ZERO(&(this->_sets[set]));
  FD_SET(this->_listener->getSocket(), &(this->_sets[set]));
  maxfd = this->_listener->getSocket();
  for (auto it = this->_sockList.begin(); it != this->_sockList.end(); it++)
  {
	tmp = (*it)->getSocket();
	FD_SET(tmp, &(this->_sets[set]));
	if (tmp > maxfd)
	  maxfd = tmp;
  }
  return (maxfd);
}

int SocketManager::Select()
{
  unsigned int nfd;

  nfd = this->_fillFDSet(READ) + 1;
  this->_fillFDSet(WRITE);
  return (select(nfd, &(this->_sets[READ]), &(this->_sets[WRITE]), &(this->_sets[ERR]), NULL));
}

ASocket *SocketManager::tryNewConnection()
{
  ASocket *newSocket;

  newSocket = NULL;
  if (FD_ISSET(this->_listener->getSocket(), &(this->_sets[READ])))
  {
	  newSocket = this->_listener->Accept();
    if (newSocket != NULL)
    {
	   this->_sockList.push_back(newSocket);
	   this->addToFDSet(newSocket, WRITE);
    }
  }
  return (newSocket);
}

void SocketManager::addToFDSet(ASocket *socket, FDSetType set)
{
  if (!socket)
	throw "null pointer";
  FD_SET(socket->getSocket(), &(this->_sets[set]));
}

bool SocketManager::isSocketAvailable(ASocket *socket, FDSetType set) const
{
  if (!socket)
	return (false);
  return (FD_ISSET(socket->getSocket(), &(this->_sets[set])));
}

