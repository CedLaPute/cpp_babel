//
// Created by lemonti on 11/3/16.
//

#include "User.hh"

User::User()
{
  this->_fd = -1;
  this->_name = "undefined";
}

User::User(int fd)
{
  this->_fd = fd;
  this->_name = "undefined";
}

User::User(int fd, const std::string name)
{
  this->_fd = fd;
  this->_name = name;
}

User::~User()
{
}

int   User::addContact(const std::string contact)
{
  auto it = this->_contactList;

  while (it != this->_contactList.end())
  {
    if (*it == contact)
      return (1);
    it++;
  }
  this->_contactList.push_back(contact);
  return (0);
}

std::string		User::getName() const
{
  return (this->_name);
}

void			User::setName(const std::string name)
{
  this->_name = name;
}

int 			User::getFD() const
{
  return (this->_fd);
}

void			User::setFD(int fd)
{
  this->_fd = fd;
}

