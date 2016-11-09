//
// Command.cpp for Command in /home/montav_c/rendu/cpp_babel/Client/ClientBabel/ClientBabel/Common/Sources
// 
// Made by Cedric MONTAVON
// Login   <montav_c@epitech.eu>
// 
// Started on  Wed Nov  9 18:38:04 2016 Cedric MONTAVON
// Last update Wed Nov  9 18:38:04 2016 Cedric MONTAVON
//

# include "../Headers/Command.hh"
# include <iostream>
# include <sstream>
# include <cstring>

Command::Command()
{

}

char 	*Command::_login()
{
	char 	*str = new char[sizeof(Buff) + _name.size()];

	Buffer::getCmd(str, _name.size(), 102, _name.c_str());
	return str;
}

char 	*Command::analyse(char *str)
{
	Buff 	*_entry = new Buff();

	_entry = Buffer::getValue(str);
	switch ((int)_entry->cmd)
	{
		case 101:
			return _login();
			break;
		case 103:
			std::cout << _entry->data << std::endl;
			break;
		case 230:
			std::cout << "Login deja existant" << std::endl;
			break;
		case 231:
			std::cout << "Pas de data transmise" << std::endl;
			break;
		case 240:
			std::cout << "Commande inconnue" << std::endl;
		default: break;
	}
	return NULL;
}

void 	Command::setName(const std::string &name)
{
	_name = name;
}


