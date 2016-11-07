//
// Created by lemonti on 11/7/16.
//

#include <string.h>
#include <sstream>
#include <iostream>
#include "WinSocket.hh"

WinSocket::WinSocket(short port)
{
  std::stringstream errStringStream;

  ZeroMemory(&(this->_resources), sizeof(this->_resources));
  this->_resources.ai_family = AF_INET;
  this->_resources.ai_socktype = SOCK_STREAM;
  this->_resources.ai_protocol = IPPROTO_TCP;
  this->_resources.ai_flags = AI_PASSIVE;
  this->_port = port;
  this->_socket = INVALID_SOCKET;
  if (getaddrinfo(NULL, this->_port, &(this->_resources), &(this->_result)) == SOCKET_ERROR)
  {
    WSACleanup();
    throw "getaddrinfo failed";
  }
  this->_socket = socket(this->_result.ai_family, this->_result.ai_socktype,
                         this->_result.ai_protocol);
  if (this->_socket == SOCKET_ERROR)
  {
    WSACleanup();
    throw "socket failed"
  }
}

WinSocket::WinSocket(int socket, struct addrinfo *result)
{
  this->_socket = socket;
  this->_result = *result;
}

WinSocket::~WinSocket()
{
}

bool WinSocket::listen()
{
  (void)port;
  if (bind(this->_socket, this->_result.ai_addr, this->_result.ai_addrlen) < 0)
	throw "bind failed";
  if (listen(this->_fd, 255) < 0)
	throw "listen failed";
  return (true);
}

LinSocket *LinSocket::accept()
{
  LinSocket *newSocket;
  struct sockaddr_in saddr;
  int clientFD;

  if ((clientFD = accept(this->_fd, reinterpret_cast<struct sockaddr *>(&saddr), NULL)) < 0)
	throw "accept failed";
  newSocket = new LinSocket(clientFD, saddr);
  return (newSocket);
}

bool LinSocket::connect(const std::string &ip, short port)
{
  struct sockaddr_in saddr;

  saddr.sin_family = AF_INET;
  saddr.sin_addr = inet_addr(ip.c_str());
  saddr.sin_port = htons(port);
  if (connect(this->_fd, reinterpret_cast<struct sockaddr *>(&(this->_saddr)), sizeof(struct sockaddr_in)) < 0)
	throw "connect failed";
  return (true);
}

char *LinSocket::receive() const
{
  char *buff = new char[256];

  memset(buff, 0, 256);
  if (read(this->_fd, buff, 255) < 0)
	throw "read failed";
  return (buff);
}

bool LinSocket::send(const char *message) const
{
  if (write(this->_fd, message, strlen(messge)) < 0)
	throw "write failed";
  return (true);
}