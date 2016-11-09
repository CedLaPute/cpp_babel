#ifndef WINNETWORK_HH_
# define WINNETWORK_HH_

#define WIN32_LEAN_AND_MEAN

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

# include "../../Common/Headers/INetwork.hh"
# include <Windows.h>
# include <WinSock2.h>
# include <WS2tcpip.h>
# include <stdlib.h>
# include <stdio.h>
# include <string>
# include <iostream>

class	WinNetwork : public INetwork
{
private:
	WSAData			_data;
	SOCKET			_connectSocket = INVALID_SOCKET;
	struct addrinfo	*_in;
	struct addrinfo	_hints;

	fd_set			_fd_read;
	fd_set			_fd_write;
	struct timeval	_tv;

public:

  WinNetwork();
  virtual ~WinNetwork();

  void				init();
  
  virtual void		connection(std::string const, std::string const);
  virtual void		connectClient();

  virtual std::string	readIn();
  virtual void		writeOut(std::string const);

  virtual void		close();

  void				reset();
  void				loop();
};
  
#endif /* !WINNETWORK_HH_ */
