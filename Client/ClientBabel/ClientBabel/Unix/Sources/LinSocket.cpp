//
// Created by lemonti on 11/7/16.
//

#include <string.h>
#include <iostream>
#include <LinSocket.hh>

LinSocket::LinSocket(short port, const char *protocol)
{
  struct protoent *pe;

  _command = new Command();
  _command->setName("Kaaris");
  _tv.tv_sec = 0;
  _tv.tv_usec = 1;
  if ((pe = getprotobyname(protocol)) == NULL)
    return ;
  this->_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  this->_port = port;
  if (this->_fd == -1)
	throw "socket failed";
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
  char *buff = new char[44000];
  int   i;

  memset(buff, 0, 44000);
  if ((i = read(this->_fd, buff, 43999)) < 0)
  	throw "read failed";
  else if (i > 0)
  {
    return buff;
  }
  return NULL;
}

bool LinSocket::Send(const char *message) const
{
  if (write(this->_fd, message, 44000) < 0)
	throw "write failed";
  return (true);
}

unsigned int LinSocket::getSocket() const
{
  return (this->_fd);
}

void  LinSocket::Reset()
{
  FD_ZERO(&_fdread);
  FD_ZERO(&_fdwrite);

  if (_fd != -1)
  {
    FD_SET(_fd, &_fdread);
    FD_SET(_fd, &_fdwrite);
  }
}

void  LinSocket::Loop()
{
  char  *str;
  char  *toSend;

  Reset();

  if (select(_fd + 1, &_fdread, &_fdwrite, NULL, &_tv) == -1)
    return ;

  if (FD_ISSET(_fd, &_fdread))
  {
    str = Receive();
    if ((toSend = _command->analyse(str)) != NULL)
    {
      Send(toSend);
    }
    else
    {
      close(this->_fd);
      exit(0);
    }
  }
}