//
// Created by lemonti on 11/7/16.
//

#include <iostream>
#include "SocketManager.hh"

SocketManager::SocketManager(short port)
{
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

unsigned int SocketManager::_fillFDSet(fd_set *set)
{
  unsigned int maxfd;

  if (!set)
	return (-1);
  FD_ZERO(set);
  FD_SET(this->_listener->getSocket(), set);
  maxfd = this->_listener->getSocket();
  for (auto it = this->_sockList.begin(); it != this->_sockList.end(); it++)
  {
  	FD_SET((*it)->getSocket(), set);
	  if ((*it)->getSocket() > maxfd)
	    maxfd = (*it)->getSocket();
  }
  return (maxfd);
}

void SocketManager::Select()
{
  unsigned int nfd;
  ASocket *newSocket = NULL;

  nfd = this->_fillFDSet(&(this->_read)) + 1;
  this->_fillFDSet(&(this->_write));
  this->_fillFDSet(&(this->_err));
  select(nfd, &(this->_read), &(this->_write), &(this->_err), NULL);
  if (FD_ISSET(this->_listener->getSocket(), &(this->_read)))
  {
  	newSocket = this->_listener->Accept();
    if (newSocket != NULL)
    {
      this->_sockList.push_back(newSocket);
	    std::cout << "connexion" << std::endl;
    }
  }
}