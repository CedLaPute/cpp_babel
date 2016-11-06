#ifndef UNIX_H_
# define UNIX_H_

# include "../../Common/Headers/AConnexion.h"
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

/*
// Version Unix du serveur
// Utilisation des file descriptor
*/

# define MAXFD 255

class LinConnexion : public AConnexion
{
private:
	int serverFD;
	int clientFD;
	int clientLen;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	struct timeval tv;
	struct protoent *pe;

	int 	fdType[MAXFD];
	char 	*fdBuff[MAXFD];

public:
	LinConnexion();
	~LinConnexion() {};

	virtual int receive() const;
	virtual int sendTo(const std::string &buff);
	virtual bool disconnect();

	bool selectLoop();

	virtual bool connect();
};

#endif /* !UNIX_H_ */