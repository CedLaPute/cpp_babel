//
// Created by lemonti on 11/3/16.
//

#ifndef CPP_BABEL_USERMANAGER_HH
#define CPP_BABEL_USERMANAGER_HH

#include "SocketManager.hh"
#include "User.hh"
#include "Command.hh"

class UserManager
{
  public:
	UserManager();
	~UserManager();
	User *addUser(const std::string &name, ASocket *socket);
	void removeUser(const std::string &name);
	void removeUser(const User *user);
	User *getUser(const std::string &name);
	std::string getUserList() const;
	void addPendingAuth(ASocket *socket);
	void handlePendingAuth(SocketManager &sm);
	void handleReceive(SocketManager &sm);
	void handleSend(SocketManager &sm);

  private:
	void _handleCommand(User *sender, char *cmd);
	void _sayHello(ASocket *socket);
	void _newClient(char *name, ASocket *socket);
	char *_listLogin();

	std::vector<ASocket *> _pendingAuth;
	std::vector<User *> _users;
};


#endif //CPP_BABEL_USERMANAGER_HH
