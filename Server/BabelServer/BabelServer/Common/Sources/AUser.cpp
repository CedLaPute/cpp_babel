//
// Created by lemonti on 11/3/16.
//

#include "../Headers/User.hh"

AUser::~AUser()
{
}

int   AUser::addContact(const std::string contact)
{
  auto it = this->_contactList.begin();

  while (it != this->_contactList.end())
  {
    if (*it == contact)
      return (1);
    it++;
  }
  this->_contactList.push_back(contact);
  return (0);
}

std::string		AUser::getName() const
{
  return (this->_name);
}

void			AUser::setName(const std::string name)
{
  this->_name = name;
}
