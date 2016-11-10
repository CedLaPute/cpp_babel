//
// Created by lemonti on 11/3/16.
//

#include "UserManager.hh"
#include "Buffer.hh"
#include <iostream>
#include <sstream>

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
		std::cout << "Read is set" << std::endl;
	  cmd = (*it)->Receive();
	  std::cout << Buffer::getValue(cmd)->data << std::endl;
	  if (cmd != NULL)
		this->_newClient(cmd, (*it));
	  else
		sm.removeSocket(*it);
	  clearedAuth.push_back(it);
	}
  }
  for (auto it = clearedAuth.begin(); it != clearedAuth.end(); it++)
	this->_pendingAuth.erase(*it);
}

void UserManager::handleReceive(SocketManager &)
{
//  char *cmd;
//  char *toSend;
//
//  for (auto it = this->_users.begin(); it != this->_users.end(); it++)
//  {
//	if (sm.isSocketAvailable((*it)->getSocket(), SocketManager::READ))
//	{
//	  cmd = (*it)->getSocket()->Receive();
//	  /*
//	   * l'interpretation des commandes se fera dans UserManager (pour avoir accès aux users) avec des methodes privées
//	   */
//	  if (cmd != NULL)
//	  {
//		toSend = _command->analyse(cmd, (*it));
//		if (toSend != NULL)
//		{
//		  std::cout << "adding command to client" << std::endl;
//		  (*it)->addCommand(toSend);
//		}
//	  }
//	  /*else
//	   {
//		 sm.removeSocket((*it)->getSocket());
//		 (*it)->goOffline();
//	   }*/
//	}
//  }
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
		(*it)->getSocket()->Send((char *)cmd);
		delete[] (cmd);
	  }
	  sm.removeFromFDSet((*it)->getSocket(), SocketManager::WRITE);
	}
  }
}

void UserManager::_handleCommand(User *sender, char *cmd)
{
  Buff *cmdBuff;

  (void) sender;
  cmdBuff = Buffer::getValue(cmd);
  switch (cmdBuff->cmd)
  {
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
  std::cout << Buffer::getValue(str)->data << std::endl;
  delete[] (str);
}

void UserManager::_newClient(char *cmd, ASocket *socket)
{
  User *newUser;
  Buff *cmdBuff;

  cmdBuff = Buffer::getValue(cmd);
  if (!this->getUser(reinterpret_cast<char *>(cmdBuff->data)))
  {
	newUser = this->addUser(reinterpret_cast<char *>(cmdBuff->data), socket);
	newUser->addCommand(this->_listLogin());
  }
}

char *UserManager::_listLogin()
{
  char *cmd;
  std::stringstream ss;

  for (auto it = this->_users.begin(); it != this->_users.end(); it++)
  {
	ss << (*it)->getName() << "/";
  }
  Buffer::getCmd(&cmd, static_cast<int>(ss.str().size()), 103, ss.str().c_str());
  return (cmd);
}