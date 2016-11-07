//
// Created by lemonti on 11/7/16.
//

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#ifndef CPP_BABEL_LINSOCKET_HH
#define CPP_BABEL_LINSOCKET_HH

# include <Windows.h>
# include <WinSock2.h>
# include <WS2tcpip.h>
# include <stdlib.h>
# include <stdio.h>
# include <string>

#pragma comment (lib, "Ws2_32.lib")

#include "../Common/ASocket.hh"

class WinSocket : public ASocket
{
  public:
	WinSocket(short port);
	WinSocket(SOCKET sock, struct addrinfo *saddr);
	virtual ~WinSocket();
	bool Listen();
	ASocket *Accept();
	bool Connect(const std::string& ip, short port);
	char *Receive() const;
	bool Send(const char *message) const;

  private:
	short	_port;
	struct addrinfo _resources;
	struct addrinfo *_result;
	SOCKET _socket;
};


#endif //CPP_BABEL_LINSOCKET_HH
