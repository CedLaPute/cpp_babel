#ifdef WIN32
# include "../../Windows/Headers/Windows.h"
#else
# include "../../Unix/Headers/Unix.h"
#endif

int main()
{

	// Déclaration pointeur sur interface de connexion
	// AConnection *absConnexion = NULL;

#ifdef WIN32

	// Assignation de absConnexion pour Windows
	// absConnexion = new WinConnexion(); 

#else

	// Assignation de absConnexion pour Unix
	// absConnexion = new LinConnexion();

#endif

	return (0);
}