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

int UserManager::addUser(int fd, const std::string &name)
{
  User *newUser = new User(fd, name);

  this->_users.push_back(newUser);
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
}