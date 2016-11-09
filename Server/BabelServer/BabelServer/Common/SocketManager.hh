//
// Created by lemonti on 11/7/16.
//

#ifndef CPP_BABEL_SOCKETMANAGER_HH
#define CPP_BABEL_SOCKETMANAGER_HH

#include <vector>

#ifdef _WIN32
	#include <WinSock2.h>
#elif __linux__
	#include <sys/select.h>
#endif

#include "ASocket.hh"


class SocketManager
{
  public:
	enum FDSetType
	{
	  READ = 0,
	  WRITE,
	  ERR
	};
	SocketManager(short port);
	~SocketManager();
	void addSocket(ASocket *socket);
	void removeSocket(const ASocket *socket);
	int Select();
	ASocket *tryNewConnection();
	void addToFDSet(ASocket *socket, FDSetType set);
	bool isSocketAvailable(const ASocket *socket, FDSetType set) const;

  private:
	unsigned int _fillFDSet(FDSetType set);
	fd_set _sets[3];
	ASocket *_listener;
	std::vector<ASocket *> _sockList;
};


#endif //CPP_BABEL_SOCKETMANAGER_HH
