# include <iostream>
# include "SocketManager.hh"

SocketManager::SocketManager(char *ip, short port)
{
	this->_call = NULL;
	this->_client = ASocket::getNewSocket(port, "TCP");
	this->_client->Connect(ip, port);
	this->_client->setName("Kaaaaaaaris");
	this->_tv.tv_sec = 0;
	this->_tv.tv_usec = 1;
}

unsigned int SocketManager::fillFDSet()
{
	unsigned int maxfd;
	unsigned int tmp;

	FD_ZERO(&this->_fdread);
	FD_ZERO(&this->_fdwrite);
	FD_SET(this->_client->getSocket(), &this->_fdread);
	FD_SET(this->_client->getSocket(), &this->_fdwrite);
	maxfd = this->_client->getSocket();
	if (this->_call)
	{
		tmp = this->_call->getSocket();
		FD_SET(this->_call->getSocket(), &this->_fdread);
		FD_SET(this->_call->getSocket(), &this->_fdwrite);
		if (tmp > maxfd)
			maxfd = tmp;
	}
	return maxfd;
}

int SocketManager::Select()
{
	unsigned int nfd;

	nfd = fillFDSet();
	return (select(nfd, &this->_fdread, &this->_fdwrite, NULL, &this->_tv));
}

void SocketManager::handleReceive()
{
	char *cmd;

	if (isSocketAvailable(this->_client, this->_fdread))
	{
		cmd = this->_client->Receive();
		handleCommand(this->_client, cmd);
	}
	if (isSocketAvailable(this->_call, this->_fdread))
	{
		cmd = this->_call->Receive();
		handleCommand(this->_call, cmd);
	}
}

bool SocketManager::isSocketAvailable(const ASocket *socket, fd_set set) const
{
	if (!socket)
		return false;
	return (FD_ISSET(socket->getSocket(), &set) != 0);
}

/* Gestion des commandes */

void SocketManager::handleCommand(ASocket *sender, char *cmd)
{
	Buff *cmdBuff;
	char *str;

	cmdBuff = Buffer::getValue(cmd);

	/* test */
	std::cout << "magic : " << cmdBuff->magic << std::endl;
	std::cout << "cmd : " << (int)cmdBuff->cmd << std::endl;
	std::cout << "size : " << cmdBuff->size << std::endl;
	std::cout << "data : " << cmdBuff->data << std::endl;

	switch ((int)cmdBuff->cmd)
	{
		case 101:
			std::cout << "sending login" << std::endl;
			sender->Send(this->_login(sender));
			break;
		case 103:
			std::cout << cmdBuff->data << std::endl;
			break;
		case 112:
			break;
		case 114:
			this->_fillCallInfo(cmdBuff);
			break;
		case 230:
			std::cout << " Login deja existant" << std::endl;
			break;
		case 231:
			std::cout << " Pas de data transmise" << std::endl;
			break;
		case 232:
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

char 	*SocketManager::_login(const ASocket *sender)
{
	char 	*str;

	Buffer::getCmd(&str, sender->getName().size(), 102, sender->getName().c_str());
	return str;
}

void	SocketManager::_fillCallInfo(Buff *cmdBuff)
{
	Data *connectionInfo;

	connectionInfo = reinterpret_cast<Data *>(cmdBuff->data);
	this->_call = ASocket::getNewSocket(connectionInfo->port, "UDP");
	this->_call->Connect(connectionInfo->ip, connectionInfo->port);
}
