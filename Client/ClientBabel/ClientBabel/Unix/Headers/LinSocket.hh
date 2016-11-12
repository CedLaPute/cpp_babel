//
// Created by lemonti on 11/7/16.
//

#ifndef CPP_BABEL_LINSOCKET_HH
#define CPP_BABEL_LINSOCKET_HH

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netdb.h>
#include <unistd.h>
#include "../../ASocket.hh"
#include "../../Command.hh"

class LinSocket : public ASocket
{
  public:
	LinSocket(short port, const char *protocol);
	LinSocket(int fd, struct sockaddr_in *saddr);
	virtual ~LinSocket();

	virtual bool Bind();
	virtual bool Listen();
	virtual ASocket *Accept();
	virtual bool Connect(const std::string& ip, short port);
	virtual char *Receive() const;
	virtual bool Send(char *message) const;
	virtual unsigned int getSocket() const;
	std::string getName() const;
	void setName(std::string const &n);

  private:
	struct sockaddr_in _saddr;
	int _fd;
	int _callFd;
	short _port;
	std::string _name;
};


#endif //CPP_BABEL_LINSOCKET_HH
