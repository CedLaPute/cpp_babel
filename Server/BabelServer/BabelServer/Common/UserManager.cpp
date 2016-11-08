//
// Created by lemonti on 11/3/16.
//

#include "UserManager.hh"

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
  char *
  if (!this->_pendingAuth.size())
	return;
  for (auto it = this->_pendingAuth.begin(); it != this->_pendingAuth.end(); it++)
  {
	if (sm.isSocketAvailable(*it, SocketManager::WRITE));
	  // 101 "Hello"
	else if (sm.isSocketAvailable(*it, SocketManager::READ));
	{
//	  102 $Login
//	  this->addUser(name, *it);
//	  this->_pendingAuth.erase(it);
	}
  }
}