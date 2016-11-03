#include "../Headers/Windows.h"

/* Démarrage du serveur */
WinConnexion::WinConnexion()
{
	printf("initializing the winconnexion class\n");
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

	printf("getaddrinfo : ok\n");

	/* Configuration de listenSocket */
	iResult = bind(listenSocket, addressResult->ai_addr, (int)addressResult->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error : %d\n", WSAGetLastError());
		freeaddrinfo(addressResult);
		closesocket(listenSocket);
		WSACleanup();
		// throw exception
	}

	printf("bind : ok\n");

	/* Ecoute */
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("listen failed with error : %ld\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		// throw exception
	}

	printf("listen : ok\n");

	clientSocket = INVALID_SOCKET;

	/* Acceptation d'un client */
	clientSocket = accept(listenSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("accept failed with error : %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		// throw exception
	}

	printf("accept : ok\n");
}

WinConnexion::~WinConnexion()
{

}

int WinConnexion::receive(const std::string &buff, int len) const
{
	return (0);
}

int WinConnexion::send(const std::string &buff) const
{
	return (0);
}

bool WinConnexion::connect()
{
	return (false);
}

bool WinConnexion::disconnect()
{
	return (false);
}

