//
// Created by lemonti on 11/7/16.
//

#ifndef CPP_BABEL_LINSOCKET_HH
#define CPP_BABEL_LINSOCKET_HH

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "ASocket.hh"

class LinSocket : public ASocket
{
  public:
	LinSocket();
	LinSocket(int fd, struct sockaddr_in *saddr);
	virtual ~LinSocket();
	bool listen();
	LinSocket *accept();
	bool connect(const std::string& ip, short port);
	char *receive() const;
	bool send(const char *message) const;

  private:
	struct sockaddr_in _saddr;
	int _fd;
	short _port;
};


#endif //CPP_BABEL_LINSOCKET_HH
