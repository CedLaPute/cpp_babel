#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#ifndef WINDOWS_H_
# define WINDOWS_H_

# include "../../Common/Headers/AConnexion.h"
# include <Windows.h>
# include <winsock.h>
# include <WS2tcpip.h>
# include <stdlib.h>
# include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")

/*
// Version Windows du serveur
// Utilisation de WSAStartup et d'un handle
*/

class WinConnexion : AConnexion
{
private:
	WSADATA wsaData;
	SOCKET listenSocket;
	SOCKET readSocket;
	struct addrinfo *addressResult = NULL;
	struct addrinfo addressResources;
	int iResult;

public:
	WinConnexion();
	~WinConnexion();

	virtual int receive(const std::string &buff, int len) const;
	virtual int send(const std::string &buff) const;
	virtual bool connect();
	virtual bool disconnect();
};

#endif /* !WINDOWS_H_ */