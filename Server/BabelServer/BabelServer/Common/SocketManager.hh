//
// Created by lemonti on 11/7/16.
//

#ifndef CPP_BABEL_SOCKETMANAGER_HH
#define CPP_BABEL_SOCKETMANAGER_HH

#include <vector>
#include <sys/select.h>
#include "ASocket.hh"


class SocketManager
{
  public:
	SocketManager(short port);
	~SocketManager();
	void addSocket(ASocket *socket);
	bool removeSocket();
	void Select();

  private:
	unsigned int _fillFDSet(fd_set *);
	fd_set _read;
	fd_set _write;
	fd_set _err;
	ASocket *_listener;
	std::vector<ASocket *> _sockList;
};


#endif //CPP_BABEL_SOCKETMANAGER_HH