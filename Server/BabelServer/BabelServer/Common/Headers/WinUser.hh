//
// Created by lemonti on 11/6/16.
//

#ifndef CPP_BABEL_WINUSER_HH
#define CPP_BABEL_WINUSER_HH

#include "../Headers/AUser.hh"

class WinUser : public AUser
{
  public:
	WinUser();
	WinUser(const std::string& name);
	virtual ~WinUser();
	void setSocket(SOCKET sock);

  private:
	SOCKET sock;
};


#endif //CPP_BABEL_WINUSER_HH
