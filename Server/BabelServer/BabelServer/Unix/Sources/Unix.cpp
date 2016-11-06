# include "../Headers/Unix.h"

/* Démarrage du serveur */
LinConnexion::LinConnexion()
{
	memset(fdType, 0, MAXFD);
	memset(fdBuff, 0, sizeof(fdBuff));
	clientLen = sizeof(struct sockaddr_in);
}

int LinConnexion::receive() const
{
	char buff[44000];
	int result;

	memset(buff, 0, sizeof(buff));
	if ((result = read(clientFD, buff, 43999)) < 0)
		throw "read failed";
	if (result > 0)
		printf("readed : %s\n", buff);
	return result;
}

int LinConnexion::sendTo(const std::string &buff)
{
	int result;

	if ((result = write(clientFD, (char *)buff.c_str(), buff.size())) < 0)
		throw "write failed";
	return result;
}

bool	LinConnexion::disconnect()
{
	return (false);
}

bool	LinConnexion::selectLoop()
{
	fd_set fd_read;
	fd_set fd_write;
	int fd_max;

	while (1)
	{
		FD_ZERO(&fd_read);
		FD_ZERO(&fd_write);
		fd_max = 0;
	
		int i;

		for (i = 0; i < MAXFD; i++)
		{
			if (fdBuff[i] != NULL)
				FD_SET(i, &fd_write);
			if (fdType[i] > 0)
			{
				FD_SET(i, &fd_read);
				fd_max = i;
			}
		}

		if (select(fd_max + 1, &fd_read, &fd_write, NULL, &tv) == -1)
			throw "select failed";

		for (i = 0; i < MAXFD; i++)
		{
			if (FD_ISSET(i, &fd_read))
			{
				switch (fdType[i])
				{
					case 1:
						printf("waiting for accept\n");
						clientFD = accept(serverFD, (struct sockaddr *)&clientAddress, (socklen_t*)&clientLen);
						
						if (clientFD > 0)
						{
							fdType[clientFD] = 2;
							printf("fdType[%d] = %d\n", clientFD, fdType[clientFD]);
							printf("client added\n");
							sendTo("HelloWorld!");
						}
						break;
					case 2:
						clientFD = i;
						receive();
						break;
					default:
						break;
				}
			}
			if (FD_ISSET(i, &fd_write))
			{
				printf("fd_write is set on i : %d\n", i);
				fdBuff[i] = NULL;
			}
		}
	}
}

bool	LinConnexion::connect()
{
	printf("initializing linux server\n");
	/* Création de la socket */
	serverFD = socket(AF_INET, SOCK_STREAM, 0);
	if (serverFD == -1)
	{
		throw "socket failed";
	}

	fdType[serverFD] = 1;
	printf("fdType[%d] = %d\n", serverFD, fdType[serverFD]);

	printf("socket ok\n");

	/* Préparation des ressources */
	tv.tv_sec = 0;
	tv.tv_usec = 1;
	pe = getprotobyname("TCP");
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(2727);

	/* Bind */
	if (bind(serverFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
	{
		throw "bind failed";
	}
	printf("bind ok\n");

	/* Listen */
	if (listen(serverFD, MAXFD) < 0)
	{
		throw "listen failed";
	}

	printf("listen ok\n");

	selectLoop();

	return (true);
}