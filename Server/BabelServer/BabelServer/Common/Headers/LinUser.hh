//
// Created by lemonti on 11/6/16.
//

#ifndef CPP_BABEL_LINUSER_HH
#define CPP_BABEL_LINUSER_HH

#include "../Headers/AUser.hh"

class LinUser : public AUser
{
  public:
	LinUser();
	LinUser(const std::string& name);
	virtual ~LinUser();
	void setSocket(int sock);

  private:
	int _sock;
};


#endif //CPP_BABEL_LINUSER_HH
