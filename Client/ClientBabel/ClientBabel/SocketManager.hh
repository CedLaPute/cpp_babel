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
	ASocket *_clientToServer;
	ASocket *_clientToClient;
	fd_set _fdread;
	fd_set _fdwrite;
	struct timeval _tv;

	/* Gestion des commandes */

	std::vector<char *> _pendingCommandsToServer;
	std::vector<char *> _pendingCommandsToClient;

	void _login(const ASocket *);
	void _acceptCall(Buff *cmdBuff);
	void _connectCall(Buff *cmdBuff);

public:
	SocketManager(char *, short);
	~SocketManager() {};
	unsigned int fillFDSet();
	int Select();
	void handleReceive();
	void handleSend();
	bool isSocketAvailable(const ASocket *, fd_set) const;

	/* Gestion des commandes */
	void addPendingCommandToServer(char *);
	void addPendingCommandToClient(char *);
	char *getPendingCommandToServer();
	char *getPendingCommandToClient();
	void handleCommand(ASocket *, char *);
};

#endif //SOCKETMANAGER_HH_