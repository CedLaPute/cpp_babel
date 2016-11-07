//
// Created by lemonti on 11/7/16.
//

#include <string.h>
#include "LinSocket.hh"

LinSocket::LinSocket(short port)
{
  struct protoent *pe = new struct protoent;

  pe = getprotobyname("TCP");
  this->_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  this->_port = port;
  delete pe;
  if (this->_fd == -1)
	throw "socket failed";
}

LinSocket::LinSocket(int fd, struct sockaddr_in *saddr)
{
  this->_fd = fd;
  this->_saddr = *saddr;
}

LinSocket::~LinSocket()
{
}

bool LinSocket::listen()
{
  this->_saddr.sin_family = AF_INET;
  this->_saddr.sin_addr = INADDR_ANY;
  this->_saddr.sin_port = htons(this->_port);
  if (bind(this->_fd, reinterpret_cast<struct sockaddr *>(&(this->_saddr)), sizeof(struct sockaddr_in)) < 0)
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