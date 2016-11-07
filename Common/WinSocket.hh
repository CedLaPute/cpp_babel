//
// Created by lemonti on 11/7/16.
//

#ifndef CPP_BABEL_LINSOCKET_HH
#define CPP_BABEL_LINSOCKET_HH

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "ASocket.hh"

class WinSocket : public ASocket
{
  public:
	WinSocket(short port);
	WinSocket(SOCKET sock, struct addrinfo saddr);
	virtual ~WinSocket();
	bool listen();
	WinSocket *accept();
	bool connect(const std::string& ip, short port);
	char *receive() const;
	bool send(const char *message) const;

  private:
	struct addrinfo _resources;
	struct addrinfo _result;
	SOCKET _socket;
};


#endif //CPP_BABEL_LINSOCKET_HH
