//
// Created by lemonti on 11/7/16.
//

#ifdef _WIN32
	# include "../Windows/WinSocket.hh"
#elif __linux__
	# include "../Unix/LinSocket.hh"
#endif

# include "ASocket.hh"

ASocket *ASocket::getNewSocket(short port, const char *protocol)
{
  ASocket *ptr = NULL;

  #ifdef _WIN32

  ptr = new WinSocket(port, protocol);

  #elif __linux__

  ptr = new LinSocket(port, protocol);

  #endif

  return (ptr);
}