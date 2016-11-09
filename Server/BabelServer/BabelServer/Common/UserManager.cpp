//
// Created by lemonti on 11/3/16.
//

#include "UserManager.hh"
#include <iostream>

UserManager::UserManager()
{
}

UserManager::~UserManager()
{
}

User *UserManager::addUser(const std::string &name, ASocket *socket)
{
  User *newUser = new User(name, socket);

  this->_users.push_back(newUser);
  return (newUser);
}

void UserManager::removeUser(const std::string &name)
{
  auto it = this->_users.begin();

  while (it != this->_users.end())
  {
	if ((*it)->getName() == name)
	{
	  delete (*it);
	  this->_users.erase(it);
	  break;
	}
	it++;
  }
}

User *UserManager::getUser(const std::string &name)
{
  auto it = this->_users.begin();

  while (it != this->_users.end())
  {
	if ((*it)->getName() == name)
	  return (*it);
	it++;
  }
  return (*it);
}

void UserManager::addPendingAuth(ASocket *socket)
{
  this->_pendingAuth.push_back(socket);
}

void UserManager::handlePendingAuth(SocketManager &sm)
{
  if (!this->_pendingAuth.size())
	return;
  for (auto it = this->_pendingAuth.begin(); it != this->_pendingAuth.end(); it++)
  {
	if (sm.isSocketAvailable(*it, SocketManager::WRITE))
	{

	}
	if (sm.isSocketAvailable(*it, SocketManager::READ))
	{
	  char *buff = (*it)->Receive();

	  std::cout << buff << std::endl;
	}
  }
}

void UserManager::handleReceive(SocketManager &sm)
{
  const char *cmd;

  for (auto it = this->_users.begin(); it != this->_users.end(); it++)
  {
	if (sm.isSocketAvailable((*it)->getSocket(), SocketManager::READ))
	{
	  cmd = (*it)->getSocket()->Receive();
	  std::cout << "command : " << cmd << std::endl;
	  /*
	   * l'interpretation des commandes se fera dans UserManager (pour avoir accès aux users) avec des methodes privées
	   */
	}
  }
}

void UserManager::handleSend(SocketManager &sm)
{
  const char *cmd;

  for (auto it = this->_users.begin(); it != this->_users.end(); it++)
  {
	if (sm.isSocketAvailable((*it)->getSocket(), SocketManager::WRITE))
	{
	  while ((cmd = (*it)->getCommand()))
		(*it)->getSocket()->Send(cmd);
	  sm.removeFromFDSet((*it)->getSocket(), SocketManager::WRITE);
	}

  }
}