#ifndef UNIX_H_
# define UNIX_H_

# include "../../Common/Headers/AConnexion.h"
# include <stdio.h>
# include <stdlib.h>

/*
// Version Unix du serveur
// Utilisation des sockets et d'un file descriptor
*/

class LinConnexion : AConnexion
{
private:
	int serverFD;
	int newSocketFD;
	int portNumber;
	int clientLen;
	struct sockaddr_in *serverAddress;
	struct sockaddr_in *clientAdress;

public:
	LinConnexion();
	~LinConnexion();

	virtual int receive(const std::string &buff, int len) const;
	virtual int send(const std::string &buff) const;
	virtual bool connect();
	virtual bool disconnect();
};

#endif /* !UNIX_H_ */