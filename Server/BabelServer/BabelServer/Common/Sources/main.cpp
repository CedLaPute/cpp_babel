#ifdef _WIN32
# include "../../Windows/Headers/Windows.h"
#elif __linux__
# include "../../Unix/Headers/Unix.h"
#endif

# include <iostream>
# include "../Headers/AConnexion.h"

int main()
{
	// Déclaration du pointeur sur interface de connexion
	AConnexion *absConnexion = NULL;

#ifdef _WIN32

	try
	{
		// Assignation de absConnexion pour Windows
		printf("windows detected, launching winsock\n");
		absConnexion = new WinConnexion();
		absConnexion->connect();
	}
	catch (const std::string &err)
	{
		std::cerr << "An error occured : " << err << std::endl;
	}

#elif __linux__

	try
	{
		// Assignation de absConnexion pour Linux
		printf("unix detected, launching sockets\n");
		absConnexion = new LinConnexion();
		absConnexion->connect();
	}
	catch (const std::string &err)
	{
		std::cerr << "An error occured : " << err << std::endl;
	}
	
#endif

	return (0);
}