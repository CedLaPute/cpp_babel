//
// Created by lemonti on 11/6/16.
//

#ifndef CPP_BABEL_WINUSER_HH
#define CPP_BABEL_WINUSER_HH

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

# include "../Common/AUser.hh"
# include <Windows.h>
# include <WinSock2.h>
# include <WS2tcpip.h>
# include <stdlib.h>
# include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")

class WinUser : public AUser
{
  public:
	WinUser();
	WinUser(const std::string& name);
	virtual ~WinUser();
	void setSocket(SOCKET sock);

  private:
	SOCKET _sock;
};


#endif //CPP_BABEL_WINUSER_HH
