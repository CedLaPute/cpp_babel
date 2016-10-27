#ifdef WIN32
# include "../../Windows/Headers/Windows.h"
#else
# include "../../Unix/Headers/Unix.h"
#endif

# include "../Headers/AConnexion.h"

int main()
{

	// Déclaration du pointeur sur interface de connexion
	AConnexion *absConnexion;

#ifdef WIN32

	// Assignation de absConnexion pour Windows
	absConnexion = new WinConnexion();

#else

	// Assignation de absConnexion pour Linux
	// absConnexion = new LinConnexion();

#endif

	return (0);
}