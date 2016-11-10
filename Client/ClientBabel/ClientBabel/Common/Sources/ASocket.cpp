//
// Created by lemonti on 11/7/16.
//

#ifdef _WIN32
	# include "../../Windows/Headers/WinSocket.hh"
#elif __linux__
	# include "../../Unix/Headers/LinSocket.hh"
#endif

# include "../Headers/ASocket.hh"

ASocket *ASocket::getNewSocket(short port)
{
  (void)port;
  ASocket *ptr = NULL;

  #ifdef _WIN32

  ptr = new WinSocket(port, "TCP");

  #elif __linux__

  printf("__linux__ detected, initializing LinSocket\n");
  ptr = new LinSocket(port, "TCP");

  #endif

  return (ptr);
}