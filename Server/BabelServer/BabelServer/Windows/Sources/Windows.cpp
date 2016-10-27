#include "../Headers/Windows.h"

/* Démarrage du serveur */
WinConnexion::WinConnexion()
{
	/* Initialisation de la Winsock */
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		// throw exception
	}
	ZeroMemory(&addressResources, sizeof(addressResources));
	addressResources.ai_family = AF_INET;
	addressResources.ai_socktype = SOCK_STREAM;
	addressResources.ai_protocol = IPPROTO_TCP;
	addressResources.ai_flags = AI_PASSIVE;

	/* Resoudre addresse - port */
	iResult = getaddrinfo(NULL, "4242", &addressResources, &addressResult);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		// throw exception
	}

	/* Configuration de listenSocket */
	iResult = bind(listenSocket, addressResult->ai_addr, (int)addressResult->ai_addrlen);

}

WinConnexion::~WinConnexion()
{

}

int WinConnexion::receive(const std::string &buff, int len) const
{

}

int WinConnexion::send(const std::string &buff) const
{

}

bool WinConnexion::connect()
{
	return (false);
}

bool WinConnexion::disconnect()
{
	return (false);
}

