//
// Created by lemonti on 11/6/16.
//

#include "WinUser.hh"

WinUser::WinUser()
{
  this->_name = "undefined";
}

WinUser::WinUser(const std::string& name)
{
  this->_name = name;
}

WinUser::~WinUser()
{
}

void WinUser::setSocket(SOCKET sock)
{
  this->_sock = sock;
}