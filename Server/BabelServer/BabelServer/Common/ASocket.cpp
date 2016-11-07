//
// Created by lemonti on 11/7/16.
//

#ifdef _WIN32
	# include "../Windows/WinSocket.hh"
#elif __linux__
	# include "../Unix/LinSocket.hh"
#endif

# include "ASocket.hh"

ASocket *ASocket::getSocket()
{
  ASocket *ptr = NULL;

  #ifdef _WIN32

  ptr = new WinSocket(2727);

  #elif __linux__

  printf("__linux__ detected, initializing LinSocket\n");
  ptr = new LinSocket(2727);

  #endif

  return (ptr);
}