//
// Created by lemonti on 11/3/16.
//

#ifndef CPP_BABEL_USER_HH
#define CPP_BABEL_USER_HH

# include <string>
# include <vector>
# include "ASocket.hh"

class User
{
  public:
	User(const std::string& name, ASocket *socket);
	~User();
	std::string getName() const;
	void setName(const std::string name);
	int addContact(const std::string contact);
	void goOnline(ASocket *socket);
	void goOffline();
	const ASocket *getSocket() const;

  protected:
	std::string _name;
	ASocket *_socket;
	bool _isOnline;
	std::vector<std::string> _contactList;
};


#endif //CPP_BABEL_USER_HH
