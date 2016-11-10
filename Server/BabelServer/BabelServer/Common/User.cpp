//
// Created by lemonti on 11/3/16.
//

#include "User.hh"
#include <iostream>

User::User(const std::string &name, ASocket *socket)
{
  this->_name = name;
  if ((this->_socket = socket))
	this->_isOnline = true;
  else
	this->_isOnline = false;
}

User::~User()
{
}

int User::addContact(const std::string contact)
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

std::string User::getName() const
{
  return (this->_name);
}

void User::setName(const std::string name)
{
  this->_name = name;
}

void User::goOnline(ASocket *socket)
{
  this->_isOnline = true;
  this->_socket = socket;
}

void User::goOffline()
{
  this->_isOnline = false;
  this->_socket = NULL;
}

const ASocket *User::getSocket() const
{
  return (this->_socket);
}

void User::addCommand(const char *command)
{
  std::cout << "size of _pendingCommands before addCommand : " << this->_pendingCommands.size() << std::endl;
  this->_pendingCommands.push_back(command);
  std::cout << "size of _pendingCommands after addCommand : " << this->_pendingCommands.size() << std::endl;
}

const char *User::getCommand()
{
  const char *cmd;

  if (!this->_pendingCommands.size())
	return (NULL);
  std::cout << "size of _pendingCommands before getCommand : " << this->_pendingCommands.size() << std::endl;
  cmd = (this->_pendingCommands.front());
  this->_pendingCommands.erase(this->_pendingCommands.begin());
  std::cout << "size of _pendingCommands after getCommand : " << this->_pendingCommands.size() << std::endl;
  return (cmd);
}