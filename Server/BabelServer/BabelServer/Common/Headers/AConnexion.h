#ifndef ACONNEXION_H_
# define ACONNEXION_H_

# include <string>

/* 
// Interface du serveur
// Le démarrage du serveur se fait dans le constructeur de la classe fille
// La boucle se fait dans le main
*/

class AConnexion
{
public:
	virtual ~AConnexion() {};

	virtual int receive(const std::string &buff, int len) const = 0;
	virtual int sendTo(const std::string &buff) = 0;
	virtual bool connect() = 0;
	virtual bool disconnect() = 0;
};

#endif /* !ACCONEXION_H_ */