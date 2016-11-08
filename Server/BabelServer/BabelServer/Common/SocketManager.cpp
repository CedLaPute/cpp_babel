//
// Created by lemonti on 11/7/16.
//

#include <iostream>
#include "SocketManager.hh"

SocketManager::SocketManager(short port)
{
/*  #ifdef _WIN32

  WSAData wsaData;
  WSAStartup(MAKEWORD(2, 2), &wsaData);

  #endif
  */
  this->_listener = ASocket::getNewSocket(port);
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
	FD_SET((tmp = (*it)->getSocket()), &(this->_sets[set]));
	if (tmp > maxfd)
	  maxfd = tmp;
  }
  return (maxfd);
}

int SocketManager::Select()
{
  unsigned int nfd;

  nfd = this->_fillFDSet(&(this->_sets[READ])) + 1;
  return (select(nfd, &(this->_sets[READ]), &(this->_sets[WRITE]), &(this->_sets[ERR]), NULL));
}

ASocket *SocketManager::tryNewConnection()
{
  ASocket *newSocket;

  if (FD_ISSET(this->_listener->getSocket(), this->_read))
  {
	newSocket = this->_listener->Accept();
	this->_sockList.push_back(newSocket);
	this->addToFDSet(newSocket, WRITE);
	return (newSocket);
  }
  return (NULL);
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

