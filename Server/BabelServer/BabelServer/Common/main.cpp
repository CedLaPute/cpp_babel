#ifdef _WIN32
# include "../Windows/WinSocket.hh"
#elif __linux__
# include "../Unix/LinSocket.hh"
#endif

# include "ASocket.hh"
# include <iostream>
# include <vector>

int main()
{
	try
	{
		std::vector<ASocket *>	_sockets; // TEST

		ASocket *absSocket = ASocket::getSocket();

		if (absSocket == NULL)
			throw "getSocket failed";

		printf("getSocket ok\n");

		absSocket->Listen();
		_sockets.push_back(absSocket);
	}
	catch (const std::string &err)
	{
		std::cerr << err << std::endl;
	}
	return (0);
}
