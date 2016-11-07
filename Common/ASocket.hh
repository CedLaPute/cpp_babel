//
// Created by lemonti on 11/7/16.
//

#ifndef CPP_BABEL_ASOCKET_HH
#define CPP_BABEL_ASOCKET_HH

#include <string>

class ASocket
{
  public:
	virtual ~ASocket();
	bool listen() = 0;
	int accept() = 0;
	bool connect(const std::string& ip, short port) = 0;
	char *receive() const = 0;
	bool send(char *message) const = 0;
	static ASocket *getSocket() const;
};


#endif //CPP_BABEL_ASOCKET_HH
