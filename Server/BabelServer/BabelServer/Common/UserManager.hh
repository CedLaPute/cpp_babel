//
// Created by lemonti on 11/3/16.
//

#ifndef CPP_BABEL_USERMANAGER_HH
#define CPP_BABEL_USERMANAGER_HH

#include "SocketManager.hh"
#include "User.hh"
#include "Command.hh"

typedef struct
{
  char ip[20];
  int port;
  char login[128];
} Data;

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
	void _handleCommand(SocketManager &sm, User *sender, char *cmd);
	void _sayHello(ASocket *socket);
	void _newClient(SocketManager &sm, char *name, ASocket *socket);
	char *_listLogin() const;
	User *_updateLogin(User *sender, char *data);
	User *_callRequest(User *sender, char *data);
	User *_callAccepted(User *sender, char *data);
	User *_callRefused(User *sender, char *data);
	User *_callFailed(User *sender, char *data);
	User *_callEnd(User *sender, char *data);
	void _quit(SocketManager &sm, User *sender);
	void _dispatchLoginList(SocketManager &sm) const;
	char *_errLoginTaken() const;
	char *_errNoData() const;
	char *_errNoSuchLogin() const;
	char *_errLoginTooLong() const;
	char *_errConnectionRefused() const;
	char *_errConnectionFailed() const;
	char *_errNotConnected() const;
	char *_errUnknownCommand() const;
	std::vector<ASocket *> _pendingAuth;
	std::vector<User *> _users;
};


#endif //CPP_BABEL_USERMANAGER_HH
