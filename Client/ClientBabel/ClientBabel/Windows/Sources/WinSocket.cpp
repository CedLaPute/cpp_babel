//
// Created by lemonti on 11/7/16.
//

#include <string.h>
#include <sstream>
#include <iostream>
#include <sstream>
#include "../../Common/Headers/ASocket.hh"
#include "../Headers/WinSocket.hh"

WinSocket::WinSocket(short port, const char *protocol)
{
  int	i;
  WSAData wsaData;

  _command = new Command();
  i = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (i != 0)
  {
	  throw "WSAStartup failed";
  }

  std::cout << "WSAStartup ok" << std::endl;

  ZeroMemory(&(this->_resources), sizeof(this->_resources));
  this->_resources.ai_family = AF_UNSPEC;
  this->_resources.ai_socktype = SOCK_STREAM;
  this->_resources.ai_protocol = getprotobyname(protocol)->p_proto;
  
  this->_tv.tv_sec = 0;
  this->_tv.tv_usec = 1;
}

WinSocket::WinSocket(SOCKET sock, struct addrinfo *saddr)
{
  this->_socket = sock;
  this->_result = saddr;
}

WinSocket::~WinSocket()
{
	WSACleanup();
}

bool WinSocket::Bind()
{
	if (bind(this->_socket, this->_result->ai_addr, this->_result->ai_addrlen) == SOCKET_ERROR)
	throw "bind failed";
	  std::cout << "bind ok" << std::endl;
	return (true);
}

bool WinSocket::Listen()
{
  return (true);
}

ASocket *WinSocket::Accept()
{
  return (NULL);
}

bool WinSocket::Connect(const std::string &ip, short port)
{
	std::ostringstream oss;
	std::string portString;

	oss << port;
	portString = oss.str();

	if (getaddrinfo(ip.c_str(), portString.c_str(), &_resources, &_result) != 0)
	{
		WSACleanup();
		return (false);
	}
	if ((_socket = socket(_result->ai_family, _result->ai_socktype, _result->ai_protocol)) == INVALID_SOCKET)
	{
		WSACleanup();
		return (false);
	}
	if (connect(_socket, _result->ai_addr, (int)_result->ai_addrlen) == SOCKET_ERROR)
	{
		WSACleanup();
		return (false);
	}
	std::cout << "Connected to server" << std::endl;
  return (true);
}

char *WinSocket::Receive() const
{
  char *buff = new char[44000];
  int i;
  std::stringstream ss;
  std::string s;

  std::cout << "in receive" << std::endl;

	memset(buff, '\0', 44000);
	if ((i = recv(this->_socket, buff, 43999, 0)) < 0)
	{
		std::cout << WSAGetLastError() << std::endl;
		throw "recv failed";
	}
	else if (i > 0)
	{
		buff[i] = '\0';
		ss << buff;
	}

  s = ss.str();
  std::cout << s.size() << std::endl;
  if (s.size() > 0)
  {
	  std::cout << Buffer::getValue((char *)s.c_str())->data << std::endl;
  }
  return ((char *)s.c_str());
}

bool WinSocket::Send(char *message) const
{
	int i;
	int size;

	Buff *_entry = Buffer::getValue(message);
	size = sizeof(Buff) + _entry->size;

  if ((i = send(this->_socket, message, size, 0)) == SOCKET_ERROR)
	throw "write failed";
  return (true);
}

unsigned int WinSocket::getSocket() const
{
	return (unsigned int)this->_socket;
}

void		WinSocket::Reset()
{
	FD_ZERO(&_fdread);
	FD_ZERO(&_fdwrite);

	if (_socket != INVALID_SOCKET)
	{
		FD_SET(_socket, &_fdread);
		FD_SET(_socket, &_fdwrite);
	}
}

void		WinSocket::Loop()
{
	char  *str;
  	char  *toSend;

	Reset();

	if (select(_socket + 1, &_fdread, &_fdwrite, NULL, &_tv) == -1)
		return;

	if (FD_ISSET(_socket, &_fdread))
	{
		str = Receive();
	    if ((toSend = _command->analyse(str)) != NULL)
	    {
	      Send(toSend);
	    }
	    else
	    {
	    	WSACleanup();
	    	exit(0);
	    }
	}
}