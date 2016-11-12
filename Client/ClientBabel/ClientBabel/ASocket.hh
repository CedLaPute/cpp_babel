//
// Created by lemonti on 11/7/16.
//

#ifndef CPP_BABEL_ASOCKET_HH
#define CPP_BABEL_ASOCKET_HH

#include <string>

class ASocket
{
  public:
	virtual ~ASocket() {};

	virtual bool Bind() = 0;
	virtual bool Listen() = 0;
	virtual ASocket *Accept() = 0;
	virtual bool Connect(const std::string &ip, short port) = 0;
	virtual char *Receive() const = 0;
	virtual bool Send(char *message) const = 0;
	virtual unsigned int getSocket() const = 0;
	virtual void Loop() = 0;
	static ASocket *getNewSocket(short port);
};


#endif //CPP_BABEL_ASOCKET_HH
