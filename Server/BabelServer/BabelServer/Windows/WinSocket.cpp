//
// Created by lemonti on 11/7/16.
//

#include <string.h>
#include <sstream>
#include <iostream>
#include <sstream>
#include "../Common/ASocket.hh"
#include "WinSocket.hh"

WinSocket::WinSocket(short port)
{
  int	i;
  WSAData wsaData;
  std::ostringstream oss;
  std::string portString;

  i = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (i != 0)
  {
	  throw "WSAStartup failed";
  }

  ZeroMemory(&(this->_resources), sizeof(this->_resources));
  this->_resources.ai_family = AF_INET;
  this->_resources.ai_socktype = SOCK_STREAM;
  this->_resources.ai_protocol = IPPROTO_TCP;
  this->_resources.ai_flags = AI_PASSIVE;
  this->_port = port;
  this->_socket = INVALID_SOCKET;
  oss << this->_port;
  portString = oss.str();
  if ((i = getaddrinfo(NULL, (char *)portString.c_str(), &(this->_resources), &(this->_result))) != 0)
  {
    WSACleanup();
    throw "getaddrinfo failed";
  }
  this->_socket = socket(this->_result->ai_family, this->_result->ai_socktype,
                         this->_result->ai_protocol);
  if (this->_socket == SOCKET_ERROR)
  {
    WSACleanup();
	throw "socket failed";
  }
}

WinSocket::WinSocket(SOCKET sock, struct addrinfo *saddr)
{
  this->_socket = sock;
  this->_result = saddr;
}

WinSocket::~WinSocket()
{
}

bool WinSocket::Listen()
{
  int i;

  (void)_port;
  if ((i = bind(this->_socket, this->_result->ai_addr, this->_result->ai_addrlen))  == SOCKET_ERROR)
	throw "bind failed";
  if (listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
		throw "listen failed";
  return (true);
}

ASocket *WinSocket::Accept()
{
  ASocket *newSocket = NULL;
  struct addrinfo *saddr = NULL;
  SOCKET client = INVALID_SOCKET;

  if ((client = accept(this->_socket, saddr->ai_addr, NULL)) < 0)
	  return NULL;
  newSocket = new WinSocket(client, saddr);
  return newSocket;
}

bool WinSocket::Connect(const std::string &ip, short port)
{
  return (true);
}

char *WinSocket::Receive() const
{
  char *buff = new char[256];

  memset(buff, 0, 256);
  if (recv(this->_socket, buff, 255, 0) < 0)
	throw "read failed";
  return (buff);
}

bool WinSocket::Send(const char *message) const
{
  if (send(this->_socket, message, (int)strlen(message), 0) < 0)
	throw "write failed";
  return (true);
}

unsigned int WinSocket::getSocket() const
{
	return (unsigned int)this->_socket;
}