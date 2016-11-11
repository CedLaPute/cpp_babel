//
// Created by lemonti on 11/3/16.
//

#include "UserManager.hh"
#include <iostream>
#include <sstream>
#include <cstring>
#include "Buffer.hh"


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
  for (auto it = this->_users.begin(); it != this->_users.end(); it++)
  {
	if ((*it)->getName() == name)
	{
	  delete (*it);
	  this->_users.erase(it);
	  break;
	}
  }
}

void UserManager::removeUser(const User *user)
{
  for (auto it = this->_users.begin(); it != this->_users.end(); it++)
  {
	if (*it == user)
	{
	  delete (*it);
	  this->_users.erase(it);
	  break;
	}
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
  return (NULL);
}

void UserManager::addPendingAuth(ASocket *socket)
{
  this->_pendingAuth.push_back(socket);
  this->_sayHello(socket);
}

void UserManager::handlePendingAuth(SocketManager &sm)
{
  char *cmd;
  std::vector<std::vector<ASocket *>::iterator> clearedAuth;

  if (!this->_pendingAuth.size())
	return;
  for (auto it = this->_pendingAuth.begin(); it != this->_pendingAuth.end(); it++)
  {
	if (sm.isSocketAvailable(*it, SocketManager::READ))
	{
	  cmd = (*it)->Receive();
	  if (cmd != NULL)
		this->_newClient(sm, cmd, (*it));
	  else
		sm.removeSocket(*it);
	  clearedAuth.push_back(it);
	}
  }
  for (auto it = clearedAuth.begin(); it != clearedAuth.end(); it++)
	this->_pendingAuth.erase(*it);
}

void UserManager::handleReceive(SocketManager &sm)
{
  char *cmd;

  for (auto it = this->_users.begin(); it != this->_users.end(); it++)
  {
	if (sm.isSocketAvailable((*it)->getSocket(), SocketManager::READ))
	{
	  cmd = (*it)->getSocket()->Receive();
	  if (cmd != NULL)
	  {
		this->_handleCommand(sm, *it, cmd);
		delete[] (cmd);
	  }
	  else
	  {
		sm.removeSocket((*it)->getSocket());
		(*it)->goOffline();
	  }
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
	  {
		(*it)->getSocket()->Send((char *) cmd);
		delete[] (cmd);
	  }
	  sm.removeFromFDSet((*it)->getSocket(), SocketManager::WRITE);
	}
  }
}

void UserManager::_handleCommand(SocketManager &sm, User *sender, char *cmd)
{
  Buff *cmdBuff;
  User *target;
  char *str;

  cmdBuff = Buffer::getValue(cmd);
  if (std::strlen(reinterpret_cast<const char *>(cmdBuff->data)) == 0)
  {
	Buffer::getCmd(&str, 0, 231, "");
	sender->addCommand(str);
	sm.addToFDSet(sender->getSocket(), SocketManager::WRITE);
	return;
  }
  switch (cmdBuff->cmd)
  {
	case 111:
	  target = this->_callCommand(sender, cmdBuff->data);
	  break;
	default:
	  std::cout << "unknown command or not implemented yet" << std::endl;
	  break;
  }
}

void UserManager::_sayHello(ASocket *socket)
{
  char *str;

  Buffer::getCmd(&str, 5, 101, "Hello");
  socket->Send(str);
  delete[] (str);
}

void UserManager::_newClient(SocketManager &sm, char *cmd, ASocket *socket)
{
  User *newUser;
  Buff *cmdBuff;
  char *str;

  cmdBuff = Buffer::getValue(cmd);
  str = NULL;
  if (std::strlen(reinterpret_cast<const char *>(cmdBuff->data)) == 0)
  {
	Buffer::getCmd(&str, 0, 231, "");
	socket->Send(str);
	delete[] (str);
	return;
  }
  if (!(newUser = this->getUser(reinterpret_cast<char *>(cmdBuff->data))))
  {
	newUser = this->addUser(reinterpret_cast<char *>(cmdBuff->data), socket);
	newUser->addCommand(this->_listLogin());
	sm.addToFDSet(socket, SocketManager::WRITE);
  }
  else if (newUser->getSocket() == NULL)
  {
	newUser->goOnline(socket);
	newUser->addCommand(this->_listLogin());
	sm.addToFDSet(socket, SocketManager::WRITE);
  }
  else
  {
	Buffer::getCmd(&str, 0, 230, "");
	socket->Send(str);
	delete[] (str);
  }
}

char *UserManager::_listLogin()
{
  char *cmd;
  std::stringstream ss;

  for (auto it = this->_users.begin(); it != this->_users.end(); it++)
  {
	if ((*it)->getSocket())
	  ss << (*it)->getName() << "/";
  }
  Buffer::getCmd(&cmd, static_cast<int>(ss.str().size()), 103, ss.str().c_str());
  return (cmd);
}

User *UserManager::_callCommand(User *sender, char *data)
{
  User *target;
  Data *connectionInfo;
  char *cmd;

  connectionInfo = reinterpret_cast<Data *>(data);
  target = this->getUser(connectionInfo->login);
  if (!target)
  {
	Buffer::getCmd(&cmd, 0, 232, "");
	sender->addCommand(cmd);
	return (sender);
  }

}