#ifndef SOCKETMANAGER_HH_
# define SOCKETMANAGER_HH_

#include <string>
#include <vector>

#ifdef _WIN32
	#include <WinSock2.h>
#elif __linux__
	#include <sys/select.h>
	#include <sys/time.h>
#endif

# include "ASocket.hh"
# include "Buffer.hh"

// Port client-client
# define PORTPTP 5956

enum SIGFORQT
{
	SENDCALL,
	LOGINNOTFREE,
	NODATA,
	LOGINTOOLONG,
	LISTLOGINS,
	NOMATCHINGLOGIN,
	INCALLORREFUSED,
	ERRORSOCKET,
	NOTCONNECTEDTOCLIENT,
	UNDEFINEDCOMMAND,
	NONE
};

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

	void _acceptCall(Buff *cmdBuff);
	void _connectCall(Buff *cmdBuff);
	void _stopCall();

	Data *_pendingCallInformation;

	/* Gestion de la communication avec Qt */
	SIGFORQT _pendingSignal;
	std::vector<std::string> _logins;

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

	/* Gestion de la communication avec Qt */
	void setName(const std::string &);
	void setLogins(char *);

	void signalAskCall(const std::string &);
	void signalAcceptCall();
	void signalRefuseCall();
	void signalStopCall();
	
	void setPendingSignal(const SIGFORQT);
	SIGFORQT getPendingSignal() const;
	std::vector<std::string> getLogins() const;
};

#endif //SOCKETMANAGER_HH_