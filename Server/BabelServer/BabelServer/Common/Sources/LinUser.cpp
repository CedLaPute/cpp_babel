//
// Created by lemonti on 11/6/16.
//

#include "../Headers/LinUser.hh"

LinUser::LinUser()
{
  this->_sock = -1;
  this->_name = "undefined";
}

LinUser::LinUser(iconst std::string& name)
{
  this->_sock = -1;
  this->_name = name;
}

LinUser::~LinUser()
{
}

void LinUser::setSocket(int sock)
{
  this->_sock = sock;
}