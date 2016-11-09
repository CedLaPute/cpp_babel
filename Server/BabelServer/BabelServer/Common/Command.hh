//
// Command.hh for Command in /home/montav_c/rendu/cpp_babel/Server/BabelServer/BabelServer/Common
// 
// Made by Cedric MONTAVON
// Login   <montav_c@epitech.eu>
// 
// Started on  Wed Nov  9 13:06:53 2016 Cedric MONTAVON
// Last update Wed Nov  9 13:06:57 2016 Cedric MONTAVON
//

#ifndef COMMAND_HH_
# define COMMAND_HH_

# include "Buffer.hh"
# include "User.hh"
# include <vector>

class Command
{
private:
	std::vector<User *> _users;

	/* Fonctions de création de commande en local */
	char 	*_unknownCommand();
	char 	*_noData();
	char	*_loginNotMatching();
	char 	*_loginNotFree();
	char 	*_loginTooLong();
	char 	*_listLogin(Buff *, User *);
	char	*_getUserInfo(Buff *, User *);

public:
	Command();
	~Command() {};

	char 	*analyse(char *, User *);

	/* Fonctions de création des commandes */
	char 	*sayHello(); // Fonction qui sera appelée lors de la connexion d'un client
	void 	setLogins(std::vector<User *>);
};

#endif /* !COMMAND_HH_ */