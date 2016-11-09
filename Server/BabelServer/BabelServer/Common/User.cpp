//
// Created by lemonti on 11/3/16.
//

#include "User.hh"

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
  this->_pendingCommands.push_back(command);
}

const char *User::sendCommand()
{
  const char *cmd;

  if (!this->_pendingCommands.size())
	return (NULL);
  cmd = *(this->_pendingCommands.front());
  this->_pendingCommands.erase(this->_pendingCommands.front());

  return (cmd);
}