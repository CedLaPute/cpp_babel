//
// Created by lemonti on 11/7/16.
//

#include <string.h>
#include <iostream>
#include <sstream>
#include <LinSocket.hh>

LinSocket::LinSocket(short port, const char *protocol)
{
  struct protoent *pe;

  if ((pe = getprotobyname(protocol)) == NULL)
	return;
  this->_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  this->_port = port;
  if (this->_fd == -1)
	throw "socket failed";
this->setName(protocol);
  std::cout << "socket ok" << std::endl;
}

LinSocket::LinSocket(int fd, struct sockaddr_in *saddr)
{
  this->_fd = fd;
  this->_saddr = *saddr;
}

LinSocket::~LinSocket()
{
}

bool LinSocket::Bind()
{
  struct sockaddr_in saddr;

  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = INADDR_ANY;
  saddr.sin_port = htons(this->_port);
  if (bind(this->_fd, reinterpret_cast<struct sockaddr *>(&saddr), sizeof(struct sockaddr_in)) < 0)
	throw "bind failed";
  std::cout << "bind ok" << std::endl;
  return (true);
}

bool LinSocket::Listen()
{
  return (true);
}

ASocket *LinSocket::Accept()
{
  return (NULL);
}

bool LinSocket::Connect(const std::string &ip, short port)
{
  struct sockaddr_in saddr;

  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = inet_addr(ip.c_str());
  saddr.sin_port = htons(port);
  if (connect(this->_fd, reinterpret_cast<struct sockaddr *>(&(saddr)), sizeof(struct sockaddr_in)) < 0)
	throw "connect failed";
  return (true);
}

char *LinSocket::Receive() const
{
  char *buff = new char[sizeof(Buff)];
  char *data;
  int i;

  if (read(this->_fd, buff, sizeof(Buff)) > 0)
  {
	data = new char[Buffer::getValue(buff)->size + sizeof(Buff)];
	memcpy(data, buff, sizeof(Buff));
	i = read(this->_fd, &data[sizeof(Buff)], Buffer::getValue(buff)->size);
	data[i + sizeof(Buff)] = 0;
	return (data);
  }
  return (NULL);
}

bool LinSocket::Send(char *message) const
{
  if (write(this->_fd, message, Buffer::getValue(message)->size + sizeof(Buff)) < 0)
	throw "write failed";
  return (true);
}

unsigned int LinSocket::getSocket() const
{
  return (this->_fd);
}

std::string LinSocket::getName() const
{
	return this->_name;
}
void LinSocket::setName(std::string const &n)
{
	this->_name = n;
}