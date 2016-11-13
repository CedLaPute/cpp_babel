# include <iostream>
# include "SocketManager.hh"

SocketManager::SocketManager(char *ip, short port)
{
	this->_clientToClient = NULL;
	this->_clientToServer = ASocket::getNewSocket(port, "TCP");
	this->_clientToServer->Connect(ip, port);
	this->_tv.tv_sec = 0;
	this->_tv.tv_usec = 1;
}

unsigned int SocketManager::fillFDSet()
{
	unsigned int maxfd;
	unsigned int tmp;

	FD_ZERO(&this->_fdread);
	FD_ZERO(&this->_fdwrite);
	FD_SET(this->_clientToServer->getSocket(), &this->_fdread);
	FD_SET(this->_clientToServer->getSocket(), &this->_fdwrite);
	maxfd = this->_clientToServer->getSocket();
	if (this->_clientToClient)
	{
		tmp = this->_clientToClient->getSocket();
		FD_SET(this->_clientToClient->getSocket(), &this->_fdread);
		FD_SET(this->_clientToClient->getSocket(), &this->_fdwrite);
		if (tmp > maxfd)
			maxfd = tmp;
	}
	return maxfd;
}

int SocketManager::Select()
{
	unsigned int nfd;

	nfd = fillFDSet() + 1;
	return (select(nfd, &this->_fdread, &this->_fdwrite, NULL, &this->_tv));
}

void SocketManager::handleSend()
{
	if (this->_pendingCommandsToServer.size())
			this->_clientToServer->Send(getPendingCommandToServer());
	if (this->_clientToClient)
	{
		if (this->_pendingCommandsToClient.size())
			this->_clientToClient->Send(getPendingCommandToClient());
	}
}

void SocketManager::handleReceive()
{
	char *cmd;

	if (isSocketAvailable(this->_clientToServer, this->_fdread))
	{
		cmd = this->_clientToServer->Receive();
		handleCommand(this->_clientToServer, cmd);
	}
	if (isSocketAvailable(this->_clientToClient, this->_fdread))
	{
		cmd = this->_clientToClient->Receive();
		handleCommand(this->_clientToClient, cmd);
	}
}

bool SocketManager::isSocketAvailable(const ASocket *socket, fd_set set) const
{
	if (!socket)
		return false;
	return (FD_ISSET(socket->getSocket(), &set) != 0);
}

/* Gestion des commandes */

void SocketManager::addPendingCommandToServer(char *cmd)
{
	this->_pendingCommandsToServer.push_back(cmd);
}

void SocketManager::addPendingCommandToClient(char *cmd)
{
	this->_pendingCommandsToClient.push_back(cmd);
}

char *SocketManager::getPendingCommandToServer()
{
	char *cmd;

	if (!this->_pendingCommandsToServer.size())
		return NULL;
	cmd = this->_pendingCommandsToServer.front();
	this->_pendingCommandsToServer.erase(this->_pendingCommandsToServer.begin());
	return cmd;
}

char *SocketManager::getPendingCommandToClient()
{
	char *cmd;

	if (!this->_pendingCommandsToClient.size())
		return NULL;
	cmd = this->_pendingCommandsToClient.front();
	this->_pendingCommandsToClient.erase(this->_pendingCommandsToClient.begin());
	return cmd;
}

void SocketManager::handleCommand(ASocket *sender, char *cmd)
{
	Buff *cmdBuff;
	cmdBuff = Buffer::getValue(cmd);

	switch ((int)cmdBuff->cmd)
	{
		case 101:
			this->_login(sender);
			std::cout << "sending login" << std::endl;
			break;
		case 103:
			std::cout << cmdBuff->data << std::endl;
			break;
		case 112:
			this->_acceptCall(cmdBuff);
			break;
		case 114:
			this->_connectCall(cmdBuff);
			break;
		case 230:
			this->setPendingSignal(LOGINNOTFREE);
			std::cout << " Login deja existant" << std::endl;
			break;
		case 231:
			this->setPendingSignal(NODATA);
			std::cout << " Pas de data transmise" << std::endl;
			break;
		case 232:
			this->setPendingSignal(NOMATCHINGLOGIN);
			std::cout << "Pas de login correspondant" << std::endl;
			break;
		case 234:
			std::cout << "Deja en call" << std::endl;
			break;
		case 235:
			std::cout << "Erreur lors de l'ouverture de la socket du client" << std::endl;
			break;
		case 240:
			std::cout << " Commande inconnue" << std::endl;
		default: break;
	}
}

void 	SocketManager::_login(const ASocket *sender)
{
	char 	*str;

	Buffer::getCmd(&str, sender->getName().size(), 102, sender->getName().c_str());
	addPendingCommandToServer(str);
}

void	SocketManager::_acceptCall(Buff *cmdBuff)
{
	char *str;
	Data *connectionInfo;

	connectionInfo = reinterpret_cast<Data *>(cmdBuff->data);
	/* Si le client est deja en appel */
	if (this->_clientToClient)
	{
		Buffer::getCmd(&str, sizeof(Data), 234, reinterpret_cast<char *>(connectionInfo));
		addPendingCommandToServer(str);
		return;
	}

	/* Demande au client d'accepter l'appel */
	// Envoi du signal


	/* Si l'user est d'accord */

	this->_clientToClient = ASocket::getNewSocket(connectionInfo->port, "UDP");
	if (!this->_clientToClient->Bind())
	{
		Buffer::getCmd(&str, sizeof(Data), 235, reinterpret_cast<char *>(connectionInfo));
		addPendingCommandToServer(str);
		return;
	}
	Buffer::getCmd(&str, sizeof(Data), 113, reinterpret_cast<char *>(connectionInfo));
	addPendingCommandToServer(str);
}

void	SocketManager::_connectCall(Buff *cmdBuff)
{
	Data *connectionInfo;

	connectionInfo = reinterpret_cast<Data *>(cmdBuff->data);
	this->_clientToClient = ASocket::getNewSocket(connectionInfo->port, "UDP");
	if (!this->_clientToClient->Connect(connectionInfo->ip, connectionInfo->port))
		return;
}

/* Gestion de la communication avec Qt */

void SocketManager::setLogins(char *)
{

}

void SocketManager::setPendingSignal(const SIGFORQT)
{

}

SIGFORQT SocketManager::getPendingSignal() const
{
	return this->_pendingSignal;
}

std::vector<std::string> SocketManager::getLogins() const
{
	return this->_logins;
}