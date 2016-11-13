# include <iostream>
# include <sstream>
# include <cstring>
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
	if (this->_pendingCommandsToServer.size())
		FD_SET(this->_clientToServer->getSocket(), &this->_fdwrite);
	maxfd = this->_clientToServer->getSocket();
	if (this->_clientToClient)
	{
		tmp = this->_clientToClient->getSocket();
		FD_SET(this->_clientToClient->getSocket(), &this->_fdread);
		if (this->_pendingCommandsToClient.size())
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
		if (cmd != NULL)
			handleCommand(this->_clientToServer, cmd);
	}
	if (isSocketAvailable(this->_clientToClient, this->_fdread))
	{
		cmd = this->_clientToClient->Receive();
		if (cmd != NULL)
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

void SocketManager::handleCommand(ASocket *, char *cmd)
{
	Buff *cmdBuff;
	cmdBuff = Buffer::getValue(cmd);

	switch ((int)cmdBuff->cmd)
	{
		case 101:
			std::cout << "Hello" << std::endl;
			break;
		case 103:
			this->setPendingSignal(LISTLOGINS);
			this->setLogins(reinterpret_cast<char *>(cmdBuff->data));
			break;
		case 112:
			this->_acceptCall(cmdBuff);
			break;
		case 114:
			this->_connectCall(cmdBuff);
			break;
		case 122:
			this->_stopCall();
			break;
		case 131:
			this->_playAudio(cmdBuff);
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
			this->_pendingCallInformation = NULL;
			this->setPendingSignal(INCALLORREFUSED);
			std::cout << "Deja en call" << std::endl;
			break;
		case 235:
			this->setPendingSignal(ERRORSOCKET);
			std::cout << "Erreur lors de l'ouverture de la socket du client" << std::endl;
			break;
		case 240:
			this->setPendingSignal(UNDEFINEDCOMMAND);
			std::cout << " Commande inconnue" << std::endl;
		default: break;
	}
}

void	SocketManager::_acceptCall(Buff *cmdBuff)
{
	char *str;
	Data *connectionInfo;

	connectionInfo = reinterpret_cast<Data *>(cmdBuff->data);
	
	std::cout << "in _acceptCall" << std::endl;
	std::cout << connectionInfo->ip << " " << connectionInfo->port << std::endl;

	/* Si le client est deja en appel */
	if (this->_clientToClient)
	{
		Buffer::getCmd(&str, sizeof(Data), 233, connectionInfo->login);
		addPendingCommandToServer(str);
		return;
	}

	/* Demande au client d'accepter l'appel */
	// Sauvegarde des informations
	this->_pendingCallInformation = connectionInfo;

	// Envoi du signal
	this->setPendingSignal(SENDCALL);
}

void	SocketManager::_connectCall(Buff *cmdBuff)
{
	Data *connectionInfo;

	connectionInfo = reinterpret_cast<Data *>(cmdBuff->data);
	this->_clientToClient = ASocket::getNewSocket(connectionInfo->port, "UDP");
	if (!this->_clientToClient->Connect(connectionInfo->ip, connectionInfo->port))
		return;
	this->_clientToClient->setName(this->_pendingCallInformation->login);
	this->setPendingSignal(CALLACCEPTED);
}

void SocketManager::_stopCall()
{
	this->_clientToClient = NULL;
}

void SocketManager::_playAudio(Buff *)
{
	// Appel de portaudio ici
  //	std::cout << cmdBuff->cmd << " " << cmdBuff->size << std::endl;
//	_pa->sendAudioFrames(this->_cod->AudioDecode(cmdBuff->data));
}

/* Gestion de la communication avec Qt */

void SocketManager::setName(const std::string &name)
{
	char 	*str;

	if (!this->_clientToServer)
		return ;
	this->_clientToServer->setName(name);
	Buffer::getCmd(&str, this->_clientToServer->getName().size(), 102, this->_clientToServer->getName().c_str());
	addPendingCommandToServer(str);
}

void SocketManager::setLogins(char *str)
{
	std::stringstream ss(str);
	std::string s;

	this->_logins.clear();
	if (str != NULL)
	{
		while (std::getline(ss, s, '\n'))
		{
			this->_logins.push_back(s);
		}
	}
}

void SocketManager::signalAskCall(const std::string &target)
{
	Data 	connectionInfo;
	char *cmd;

	connectionInfo.port = PORTPTP;
    std::memset(connectionInfo.login, 0, 128);
    std::memset(connectionInfo.ip, 0, 20);
    std::strcpy((char *)(connectionInfo.login), target.c_str());
    Buffer::getCmd(&cmd, sizeof(Data), 111, reinterpret_cast<char *>(&connectionInfo));
    addPendingCommandToServer(cmd);
    this->_pendingCallInformation = &connectionInfo;
}

void SocketManager::signalAcceptCall()
{
	char *str;

	/* Si l'user est d'accord pour décrocher */

	if (this->_pendingCallInformation)
	{
		this->_clientToClient = ASocket::getNewSocket(this->_pendingCallInformation->port, "UDP");
		if (!this->_clientToClient->Bind())
		{
			Buffer::getCmd(&str, sizeof(Data), 235, this->_pendingCallInformation->login);
			addPendingCommandToServer(str);
			return;
		}
		this->_clientToClient->setName(this->_pendingCallInformation->login);
		Buffer::getCmd(&str, sizeof(Data), 113, reinterpret_cast<char *>(this->_pendingCallInformation));
		addPendingCommandToServer(str);
	}
}

void SocketManager::signalRefuseCall()
{
	char *str;

	if (this->_pendingCallInformation)
	{
		Buffer::getCmd(&str, sizeof(Data), 233, this->_pendingCallInformation->login);
		addPendingCommandToServer(str);
		this->_pendingCallInformation = NULL;
		return;
	}
}

void SocketManager::signalStopCall()
{
	char *str;

	if (this->_clientToClient)
	{
		Buffer::getCmd(&str, sizeof(Data), 121, this->_clientToClient->getName().c_str());
		addPendingCommandToServer(str);
	}
}

void SocketManager::setPendingSignal(const SIGFORQT pendingSignal)
{
	this->_pendingSignal = pendingSignal;
}

SIGFORQT SocketManager::getPendingSignal() const
{
	return this->_pendingSignal;
}

std::vector<std::string> SocketManager::getLogins() const
{
	return this->_logins;
}
