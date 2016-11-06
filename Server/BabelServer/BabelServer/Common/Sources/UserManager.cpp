//
// Created by lemonti on 11/3/16.
//

#ifdef _WIN32
# include "../Headers/WinUser.hh"
#elif __linux__
# include "../Headers/LinUser.hh"
#endif

#include "../Headers/UserManager.hh"

UserManager::UserManager()
{
}

UserManager::~UserManager()
{
}

AUser *UserManager::addUser(const std::string &name)
{
  AUser *newUser;

  #ifdef _WIN32

  newUser = new WinUser(name);

  #elif __linux__

  newUser = new LinUser(name);

  #endif

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

AUser *UserManager::getUser(const std::string &name)
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