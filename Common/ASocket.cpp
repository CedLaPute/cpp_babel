//
// Created by lemonti on 11/7/16.
//

#include "ASocket.hh"
#include "WinSocket.hh"
#include "LinSocket.hh"

ASocket *ASocket::getSocket() const
{
  ASocket *ptr = NULL;

  #ifdef _WIN32

  ptr = new WinSocket();

  #elif __linux__

  ptr = new LinSocket();

  #endif

  return (ptr);
}