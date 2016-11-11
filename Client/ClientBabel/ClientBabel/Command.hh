//
// Command.hh for Command in /home/montav_c/rendu/cpp_babel/Client/ClientBabel/ClientBabel/Common/Headers
// 
// Made by Cedric MONTAVON
// Login   <montav_c@epitech.eu>
// 
// Started on  Wed Nov  9 18:38:16 2016 Cedric MONTAVON
// Last update Wed Nov  9 18:38:17 2016 Cedric MONTAVON
//

#ifndef COMMAND_HH_
# define COMMAND_HH_

# include "Buffer.hh"
# include <string>

class Command
{
private:
	std::string _name;

	/* Fonctions de création de commande */
	char 	*_login();

public:
	Command();
	~Command() {};

	char 	*analyse(char *);
	void 	setName(const std::string &);
};

#endif /* !COMMAND_HH_ */