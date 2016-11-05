# include "../Headers/Windows.h"
# include <sstream>
# include <string>
# include <iostream>

/* Démarrage du serveur */
WinConnexion::WinConnexion()
{
	std::stringstream	errStringStream;

	printf("initializing the winconnexion class\n");
	/* Initialisation de la Winsock */
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		errStringStream << "WSAStartup failed with error : " << iResult;
		throw (errStringStream.str());
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
		errStringStream << "getaddrinfo failed with error : " << iResult;
		WSACleanup();
		throw (errStringStream.str());
	}
	printf("getaddrinfo : ok\n");

	// Création de la socket
	listenSocket = socket(addressResult->ai_family, addressResult->ai_socktype, addressResult->ai_protocol);
	if (listenSocket == INVALID_SOCKET)
	{
		errStringStream << "socket failed with error : " << WSAGetLastError();
		freeaddrinfo(addressResult);
		WSACleanup();
		throw (errStringStream.str());
	}

	printf("socket : ok\n");

	/* Configuration de listenSocket */
	iResult = bind(listenSocket, addressResult->ai_addr, (int)addressResult->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		errStringStream << "bind failed with error : " << WSAGetLastError();
		freeaddrinfo(addressResult);
		closesocket(listenSocket);
		WSACleanup();
		throw (errStringStream.str());
	}

	printf("bind : ok\n");

	/* Ecoute */
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		errStringStream << "listen failed with error : " << WSAGetLastError();
		closesocket(listenSocket);
		WSACleanup();
		throw (errStringStream.str());
	}

	printf("listen : ok\n");
	printf("server boot : ok\n");

}

WinConnexion::~WinConnexion()
{
	WSACleanup();
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
			// throw
		}
	} while (result > 0);
	return (0);
}

int WinConnexion::sendTo(const std::string &buff)
{
	/*char *sendbuff = "Hello world!";
	int result;*/

/*	result = send(clientSocket, sendbuff, (int)strlen(sendbuff), 0);
	if (result == SOCKET_ERROR)
	{
		printf("send failed with error : %d\n", result);
		closesocket(clientSocket);
		WSACleanup();
		// throw 
	}*/

	Message		message(0, buff);

	return (0);
}

DWORD WINAPI	ProcessClient(LPVOID lpParameter)
{
	SOCKET		clientSocket = (SOCKET)lpParameter;

	printf("client added\n");
	return (0);
}

bool WinConnexion::connect()
{
	/* Acceptation d'un client */
	while (1)
	{

		clientSocket = INVALID_SOCKET;
		while (clientSocket == INVALID_SOCKET)
		{
			clientSocket = accept(listenSocket, NULL, NULL);
		}

		if (clientSocket != INVALID_SOCKET)
		{
			printf("accept : ok\n");
		}

		DWORD		dwIthreadId;
		CreateThread(NULL, 0, ProcessClient, (LPVOID)clientSocket, 0, &dwIthreadId);
	}
	return (true);
}

bool WinConnexion::disconnect()
{
	return (false);
}
