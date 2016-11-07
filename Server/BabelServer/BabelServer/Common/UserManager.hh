//
// Created by lemonti on 11/3/16.
//

#ifndef CPP_BABEL_USERMANAGER_HH
#define CPP_BABEL_USERMANAGER_HH

#include "AUser.hh"

class UserManager
{
  public:
	UserManager();
	~UserManager();
	AUser *addUser(const std::string &name);
	void removeUser(const std::string &name);
	AUser *getUser(const std::string &name);

  private:
	std::vector<AUser *> _users;
};


#endif //CPP_BABEL_USERMANAGER_HH
