//
// Created by lemonti on 11/7/16.
//

#ifndef CPP_BABEL_SOCKETMANAGER_HH
#define CPP_BABEL_SOCKETMANAGER_HH

# include "ASocket.hh"
# include <vector>

class SocketManager
{
  public:
	SocketManager();
	~SocketManager();
	bool setListenSocket();
	bool addSocket();
	bool removeSocket();

  private:
	std::vector<ASocket *> _sockList;
};


#endif //CPP_BABEL_SOCKETMANAGER_HH
