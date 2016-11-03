#ifdef _WIN32
# include "../../Windows/Headers/Windows.h"
#elif __linux__
# include "../../Unix/Headers/Unix.h"
#endif

# include "../Headers/AConnexion.h"

int main()
{

	// Déclaration du pointeur sur interface de connexion
	AConnexion *absConnexion = NULL;

#ifdef _WIN32

	// Assignation de absConnexion pour Windows
	printf("windows detected, launching winsock\n");
	absConnexion = new WinConnexion();

#elif __linux__

	// Assignation de absConnexion pour Linux
	// absConnexion = new LinConnexion();

#endif

	return (0);
}