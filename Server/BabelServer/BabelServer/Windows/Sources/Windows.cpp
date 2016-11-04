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

	listenSocket = INVALID_SOCKET;
	clientSocket = INVALID_SOCKET;
	readSocket = INVALID_SOCKET;
	addressResult = NULL;

	/* Resoudre addresse - port */
	iResult = getaddrinfo(NULL, "2727", &addressResources, &addressResult);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		// throw exception
	}
	printf("getaddrinfo : ok\n");

	// Création de la socket
	listenSocket = socket(addressResult->ai_family, addressResult->ai_socktype, addressResult->ai_protocol);
	if (listenSocket == INVALID_SOCKET)
	{
		printf("socket failed with error : %d\n", WSAGetLastError());
		freeaddrinfo(addressResult);
		WSACleanup();
		return;
		// throw exception
	}

	printf("socket : ok\n");

	/* Configuration de listenSocket */
	iResult = bind(listenSocket, addressResult->ai_addr, (int)addressResult->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error : %d\n", WSAGetLastError());
		freeaddrinfo(addressResult);
		closesocket(listenSocket);
		WSACleanup();
		return;
		// throw exception
	}

	printf("bind : ok\n");

	/* Ecoute */
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("listen failed with error : %ld\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return;
		// throw exception
	}

	printf("listen : ok\n");

}

WinConnexion::~WinConnexion()
{

}

int WinConnexion::receive(const std::string &, int len) const
{
	char recvbuff[44000];
	int recvbufflen = 44000;
	int result;;

	do
	{
		result = recv(clientSocket, recvbuff, recvbufflen, 0);
		if (result > 0)
			printf("Bytes received : %d\n", result);
		else if (result < 0)
		{
			printf("recv failed : %d\n", result);
			WSACleanup();
		}
	} while (result > 0);
	return (0);
}

int WinConnexion::sendTo(const std::string &buff)
{
	char *sendbuff = "Hello world!";
	int result;

	result = send(clientSocket, sendbuff, (int)strlen(sendbuff), 0);
	if (result == SOCKET_ERROR)
	{
		printf("send failed with error : %d\n", result);
		closesocket(clientSocket);
		WSACleanup();
	}
	return (0);
}

bool WinConnexion::connect()
{

	clientSocket = INVALID_SOCKET;

	/* Acceptation d'un client */
	while (clientSocket == INVALID_SOCKET)
	{
		clientSocket = accept(listenSocket, NULL, NULL);
		if (clientSocket != INVALID_SOCKET)
		{
			printf("accept : ok\n");
			//			printf("accept failed with error : %d\n", WSAGetLastError());
			//		closesocket(listenSocket);
			//	WSACleanup();
			// throw exception
		}
	}
	return (true);
}

bool WinConnexion::disconnect()
{
	return (false);
}

