//
// Command.cpp for Command in /home/montav_c/rendu/cpp_babel/Server/BabelServer/BabelServer/Common
// 
// Made by Cedric MONTAVON
// Login   <montav_c@epitech.eu>
// 
// Started on  Wed Nov  9 13:07:06 2016 Cedric MONTAVON
// Last update Wed Nov  9 13:07:06 2016 Cedric MONTAVON
//

# include <iostream>
# include <cstring>
# include "Command.hh"

Command::Command()
{
}

char 	*Command::_noData()
{
	char *str = new char[sizeof(Buff)];

	Buffer::getCmd(str, 0, 231, "");
	return str;
}

char	*Command::_loginNotFree()
{
	char *str = new char[sizeof(Buff)];

	Buffer::getCmd(str, 0, 230, "");
	return str;
}

char 	*Command::_listLogin()
{
	int size = _logins.size();
	char *str = new char[sizeof(Buff) + size];

	Buffer::getCmd(str, size, 103, _logins.c_str());
	return str;
}

char 	*Command::analyse(char *str)
{
	std::cout << "in analyse" << std::endl;
	std::cout << str << std::endl;

	Buff 	*_entry = new Buff();

	_entry = Buffer::getValue(str);
	std::cout << "---" << std::endl;
	std::cout << _entry->magic << std::endl;
	std::cout << _entry->size << std::endl;
	std::cout << _entry->cmd << std::endl;
	std::cout << _entry->data << std::endl;
	return (char *)_entry->data;
}

char 	*Command::sayHello()
{
	char 	*str = new char[sizeof(Buff) + 5];

	Buffer::getCmd(str, 5, 101, "Hello");
	return str;
}

void 	Command::setLogins(std::string const &logins)
{
	_logins = logins;
}