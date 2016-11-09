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
    /* USELESS - On check que le read, et on renvoie une réponses lorsque nécessaire
  	if (sm.isSocketAvailable(*it, SocketManager::WRITE))
    {
    }*/
  	if (sm.isSocketAvailable(*it, SocketManager::READ))
  	{
      char *buff = (*it)->Receive();

      std::cout << buff << std::endl;
	  }
  }
}