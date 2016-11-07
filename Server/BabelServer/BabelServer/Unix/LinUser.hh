//
// Created by lemonti on 11/6/16.
//

#ifndef CPP_BABEL_LINUSER_HH
#define CPP_BABEL_LINUSER_HH

# include "../../Common/Headers/AUser.hh"
# include <stdio.h>
# include <netdb.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/time.h>
# include <string.h>

class LinUser : public AUser
{
  public:
	LinUser();
	LinUser(const std::string& name);
	virtual ~LinUser();
	void setSocket(int sock);
	void setAddress(struct sockaddr_in address);

  private:
	int _sock;
	struct sockaddr_in _address;
};


#endif //CPP_BABEL_LINUSER_HH
