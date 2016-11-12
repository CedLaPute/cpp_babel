#ifndef SOCKETMANAGER_HH_
# define SOCKETMANAGER_HH_

#include <vector>

#ifdef _WIN32
	#include <WinSock2.h>
#elif __linux__
	#include <sys/select.h>
	#include <sys/time.h>
#endif

# include "ASocket.hh"
# include "Buffer.hh"

typedef struct
{
	char ip[20];
	int port;
	char login[128];
} Data;

class SocketManager
{
private:
	ASocket *_client;
	ASocket *_call;
	fd_set _fdread;
	fd_set _fdwrite;
	struct timeval _tv;

	char *_login(const ASocket *);
	void _fillCallInfo(Buff *cmdBuff);

public:
	SocketManager(char *, short);
	~SocketManager() {};
	unsigned int fillFDSet();
	int Select();
	void handleReceive();
	bool isSocketAvailable(const ASocket *, fd_set) const;

	/* Gestion des commandes */
	void handleCommand(ASocket *, char *);
};

#endif //SOCKETMANAGER_HH_