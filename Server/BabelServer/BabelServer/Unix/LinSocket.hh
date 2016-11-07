//
// Created by lemonti on 11/7/16.
//

#ifndef CPP_BABEL_LINSOCKET_HH
#define CPP_BABEL_LINSOCKET_HH

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include "../Common/ASocket.hh"

class LinSocket : public ASocket
{
  public:
	LinSocket(short port);
	LinSocket(int fd, struct sockaddr_in *saddr);
	virtual ~LinSocket();
	virtual bool Listen();
	virtual ASocket *Accept();
	virtual bool Connect(const std::string& ip, short port);
	virtual char *Receive() const;
	virtual bool Send(const char *message) const;

  private:
	struct sockaddr_in _saddr;
	int _fd;
	short _port;
};


#endif //CPP_BABEL_LINSOCKET_HH
