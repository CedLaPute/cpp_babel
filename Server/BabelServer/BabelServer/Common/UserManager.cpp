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
	  }
	  sm.removeFromFDSet((*it)->getSocket(), SocketManager::WRITE);
	}
  }
}

void UserManager::_handleCommand(SocketManager &sm, User *sender, char *cmd)
{
  Buff *cmdBuff;
  User *target;

  target = NULL;
  cmdBuff = Buffer::getValue(cmd);
  switch (cmdBuff->cmd)
  {
	case 102:
	  target = this->_updateLogin(sender, reinterpret_cast<char *>(cmdBuff->data));
	  if (!target)
		this->_dispatchLoginList(sm);
	  break;
	case 111:
	  if (cmdBuff->size == sizeof(Data))
		target = this->_callRequest(sender, reinterpret_cast<char *>(cmdBuff->data));
	  break;
	case 113:
	  if (cmdBuff->size == sizeof(Data))
		target = this->_callAccepted(sender, reinterpret_cast<char *>(cmdBuff->data));
	  break;
	case 121:
	  target = this->_callEnd(sender, reinterpret_cast<char *>(cmdBuff->data));
	  break;
	case 104:
	  this->_quit(sm, sender);
	  this->_dispatchLoginList(sm);
	  break;
	case 233:
	  target = this->_callRefused(sender, reinterpret_cast<char *>(cmdBuff->data));
	  break;
	case 234:
	  target = this->_callFailed(sender, reinterpret_cast<char *>(cmdBuff->data));
	  break;
	case 235:
	  target = this->_callFailed(sender, reinterpret_cast<char *>(cmdBuff->data));
	  break;
	default:
	  sender->addCommand(this->_errUnknownCommand());
	  target = sender;
	  break;
  }
  if (target)
	sm.addToFDSet(target->getSocket(), SocketManager::WRITE);
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
  if (std::strlen(reinterpret_cast<const char *>(cmdBuff->data)) == 0)
  {
	str = this->_errNoData();
	socket->Send(str);
	delete[] (str);
	return;
  }
  else if (std::strlen(reinterpret_cast<const char *>(cmdBuff->data)) > 128)
  {
	str = this->_errLoginTooLong();
	socket->Send(str);
	delete[] (str);
	return;
  }
  if (!(newUser = this->getUser(reinterpret_cast<char *>(cmdBuff->data))))
  {
	this->addUser(reinterpret_cast<char *>(cmdBuff->data), socket);
	this->_dispatchLoginList(sm);
  }
  else if (newUser->getSocket() == NULL)
  {
	newUser->goOnline(socket);
	this->_dispatchLoginList(sm);
  }
  else
  {
	str = this->_errLoginTaken();
	socket->Send(str);
	delete[] (str);
  }
}

char *UserManager::_listLogin() const
{
  char *cmd;
  std::stringstream ss;

  for (auto it = this->_users.begin(); it != this->_users.end(); it++)
  {
	if ((*it)->getSocket())
	  ss << (*it)->getName() << "\n";
  }
  Buffer::getCmd(&cmd, static_cast<int>(ss.str().size()), 103, ss.str().c_str());
  return (cmd);
}

User *UserManager::_updateLogin(User *sender, char *data)
{
  if (std::strlen(data) == 0)
	sender->addCommand(this->_errNoData());
  else if (this->getUser(data) == NULL)
  {
	sender->setName(data);
	return (NULL);
  }
  else if (this->getUser(data) == sender)
	sender->addCommand(this->_listLogin());
  else
	sender->addCommand(this->_errLoginTaken());
  return (sender);
}

User *UserManager::_callRequest(User *sender, char *data)
{
  User *target;
  Data *connectionInfo;
  char *cmd;
  char *tmp;

  connectionInfo = reinterpret_cast<Data *>(data);
  std::cout << "in _callRequest" << std::endl;
  std::cout << connectionInfo->login << " " << connectionInfo->port << std::endl;
  if (std::strlen(connectionInfo->login) == 0 || connectionInfo->port == 0)
  {
	sender->addCommand(this->_errNoData());
	return (sender);
  }
  target = this->getUser(connectionInfo->login);
  if (!target)
  {
	sender->addCommand(this->_errNoSuchLogin());
	return (sender);
  }
  else if (target->isInCall())
  {
	sender->addCommand(this->_errConnectionRefused());
	return (sender);
  }
  tmp = sender->getSocket()->getIP();
  std::strncpy(&connectionInfo->ip[0], tmp, 20);
  std::memset(&connectionInfo->login[0], 0, 128);
  std::strncpy(&connectionInfo->login[0], sender->getName().c_str(), sender->getName().size());
  Buffer::getCmd(&cmd, sizeof(Data), 112, reinterpret_cast<char *>(connectionInfo));
  target->addCommand(cmd);
  std::cout << "_callRequest done" << std::endl;
  return (target);
}

User *UserManager::_callAccepted(User *sender, char *data)
{
  User *target;
  Data *connectionInfo;
  char *cmd;
  char *tmp;

  connectionInfo = reinterpret_cast<Data *>(data);
  if (std::strlen(connectionInfo->login) == 0 || connectionInfo->port == 0)
  {
	sender->addCommand(this->_errNoData());
	return (sender);
  }
  target = this->getUser(connectionInfo->login);
  if (!target)
  {
	sender->addCommand(this->_errNoSuchLogin());
	return (sender);
  }
  tmp = sender->getSocket()->getIP();
  std::strncpy(&connectionInfo->ip[0], tmp, 20);
  std::memset(&connectionInfo->login[0], 0, 128);
  Buffer::getCmd(&cmd, sizeof(Data), 114, reinterpret_cast<char *>(connectionInfo));
  target->addCommand(cmd);
  sender->setInCallWith(target);
  target->setInCallWith(sender);
  return (target);
}

User *UserManager::_callRefused(User *sender, char *data)
{
  User *target;

  if (std::strlen(data) == 0)
  {
	sender->addCommand(this->_errNoData());
	return (sender);
  }
  target = this->getUser(data);
  if (!target)
  {
	sender->addCommand(this->_errNoSuchLogin());
	return (sender);
  }
  target->addCommand(this->_errConnectionRefused());
  return (target);
}

User *UserManager::_callFailed(User *sender, char *data)
{
  User *target;

  if (std::strlen(data) == 0)
  {
	sender->addCommand(this->_errNoData());
	return (sender);
  }
  target = this->getUser(data);
  if (!target)
  {
	sender->addCommand(this->_errNoSuchLogin());
	return (sender);
  }
  target->addCommand(this->_errConnectionFailed());
  return (target);
}

User *UserManager::_callEnd(User *sender, char *data)
{
  char *str;
  User *target;

  if (std::strlen(data) == 0)
  {
	sender->addCommand(this->_errNoData());
	return (sender);
  }
  target = this->getUser(data);
  if (target == NULL)
  {
	sender->addCommand(this->_errNoSuchLogin());
	return (sender);
  }
  if (!sender->isInCall())
  {
	sender->addCommand(this->_errNotConnected());
	return (sender);
  }
  Buffer::getCmd(&str, static_cast<int>(sender->getName().size()), 122, sender->getName().c_str());
  target->addCommand(str);
  sender->setInCallWith(NULL);
  target->setInCallWith(NULL);
  return (target);
}

void UserManager::_quit(SocketManager &sm, User *sender)
{
  sm.removeSocket(sender->getSocket());
  sender->goOffline();
}

void UserManager::_dispatchLoginList(SocketManager &sm) const
{
  char *cmd;

  cmd = this->_listLogin();
  for (auto it = this->_users.begin(); it != this->_users.end(); it++)
  {
	if ((*it)->getSocket())
	{
	  (*it)->addCommand(cmd);
	  sm.addToFDSet((*it)->getSocket(), SocketManager::WRITE);
	}
  }
}

char *UserManager::_errLoginTaken() const
{
  char *ret;

  Buffer::getCmd(&ret, 0, 230, "");
  return (ret);
}

char *UserManager::_errNoData() const
{
  char *ret;

  Buffer::getCmd(&ret, 0, 231, "");
  return (ret);
}

char *UserManager::_errLoginTooLong() const
{
  char *ret;

  Buffer::getCmd(&ret, 0, 237, "");
  return (ret);
}

char *UserManager::_errNoSuchLogin() const
{
  char *ret;

  Buffer::getCmd(&ret, 0, 232, "");
  return (ret);
}

char *UserManager::_errConnectionRefused() const
{
  char *ret;

  Buffer::getCmd(&ret, 0, 234, "");
  return (ret);
}

char *UserManager::_errConnectionFailed() const
{
  char *ret;

  Buffer::getCmd(&ret, 0, 235, "");
  return (ret);
}

char *UserManager::_errNotConnected() const
{
  char *ret;

  Buffer::getCmd(&ret, 0, 238, "");
  return (ret);
}

char *UserManager::_errUnknownCommand() const
{
  char *ret;

  Buffer::getCmd(&ret, 15, 240, "Unknown command");
  return (ret);
}