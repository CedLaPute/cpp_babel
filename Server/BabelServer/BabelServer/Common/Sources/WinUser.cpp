//
// Created by lemonti on 11/6/16.
//

#include "../Headers/WinUser.hh"

WinUser::WinUser()
{
  this->_name = "undefined";
}

WinUser::WinUser(iconst std::string& name)
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