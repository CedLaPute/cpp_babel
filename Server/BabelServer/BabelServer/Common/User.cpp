//
// Created by lemonti on 11/3/16.
//

#include <iostream>
#include "User.hh"
#include "Buffer.hh"

User::User(const std::string &name, ASocket *socket)
{
  this->_name = name;
  this->_calling = NULL;
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
  this->_calling = NULL;
  this->_socket = NULL;
}

const ASocket *User::getSocket() const
{
  return (this->_socket);
}

void User::addCommand(const char *command)
{
  this->_pendingCommands.push_back(command);
  std::cout << "cmd added : --" << (int) Buffer::getValue(const_cast<char *>(command))->cmd
			<< "--" << Buffer::getValue(const_cast<char *>(command))->data << "--" << std::endl;
}

const char *User::getCommand()
{
  const char *command;

  if (!this->_pendingCommands.size())
	return (NULL);
  command = (this->_pendingCommands.front());
  this->_pendingCommands.erase(this->_pendingCommands.begin());
  std::cout << "cmd got : --" << (int) Buffer::getValue(const_cast<char *>(command))->cmd
			<< "--" << Buffer::getValue(const_cast<char *>(command))->data << "--" << std::endl;
  return (command);
}

bool User::isInCall() const
{
  return (this->_calling != NULL);
}

void User::setInCallWith(User *user)
{
  this->_calling = user;
}