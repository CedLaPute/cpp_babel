//
// Created by lemonti on 11/7/16.
//

#include <string.h>
#include <sstream>
#include <iostream>
#include <sstream>
#include "../Common/ASocket.hh"
#include "WinSocket.hh"

WinSocket::WinSocket(short port, const char *protocol)
{
  std::ostringstream oss;
  std::string portString;
  int i;

  ZeroMemory(&(this->_resources), sizeof(this->_resources));
  this->_resources.ai_family = AF_INET;
  this->_resources.ai_socktype = SOCK_STREAM;
  this->_resources.ai_protocol = getprotobyname(protocol)->p_proto;
  this->_resources.ai_flags = AI_PASSIVE;
  this->_port = port;
  this->_socket = INVALID_SOCKET;
  oss << this->_port;
  portString = oss.str();
  if ((i = getaddrinfo(NULL, (char *) portString.c_str(), &(this->_resources), &(this->_result))) != 0)
  {
	WSACleanup();
	throw "getaddrinfo failed";
  }

  std::cout << "getaddrinfo ok" << std::endl;

  this->_socket = socket(this->_result->ai_family, this->_result->ai_socktype,
						 this->_result->ai_protocol);

  std::cout << "socket ok" << std::endl;

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
  (void) _port;

  if (listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
	throw "listen failed";

  std::cout << "listen ok" << std::endl;

  return (true);
}

ASocket *WinSocket::Accept()
{
	ASocket *newSocket = NULL;
	SOCKET client = INVALID_SOCKET;

	if ((client = accept(this->_socket, NULL, NULL)) < 0)
	throw "Accept failed";
	if (client != INVALID_SOCKET)
	{
		std::cout << "NewSocket detected" << std::endl;
		newSocket = new WinSocket(client, NULL);
		return newSocket;
	}
	else
		std::cout << "NULL" << std::endl;
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
	char *buff = new char[sizeof(Buff)];
	char *data;
	int i;

	if (recv(this->_socket, buff, sizeof(Buff), 0) > 0)
	{
		data = new char[Buffer::getValue(buff)->size + sizeof(Buff)];
		memcpy(data, buff, sizeof(Buff));
		i = recv(this->_socket, &data[sizeof(Buff)], Buffer::getValue(buff)->size, 0);
		data[i + sizeof(Buff)] = 0;
		return (data);
	}
	return (NULL);
}

bool WinSocket::Send(char *message) const
{
	int i;
	int size;
	Buff	*_entry;

	_entry = Buffer::getValue(message);
	size = sizeof(Buff) + _entry->size;

	if ((i = send(this->_socket, message, size, 0)) == SOCKET_ERROR)
	{
		std::cout << WSAGetLastError() << std::endl;
		return false;
	}
  return (true);
}

unsigned int WinSocket::getSocket() const
{
  return this->_socket;
}

char *WinSocket::getIP() const
{
	char *str = new char[INET6_ADDRSTRLEN];
	struct sockaddr_in *addr;

	addr = reinterpret_cast<struct sockaddr_in *>(this->_result->ai_addr);
	InetNtop(AF_INET, &(addr->sin_addr), str, INET6_ADDRSTRLEN);
	return str;
}

int WinSocket::getPort() const
{
	return (this->_port);
}