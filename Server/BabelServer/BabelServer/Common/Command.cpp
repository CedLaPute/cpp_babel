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
# include <sstream>
# include <cstring>
# include "Command.hh"

Command::Command()
{
}

char 	*Command::_unknownCommand()
{
	char *str;

	Buffer::getCmd(&str, 0, 240, "");
	return str;
}

char	*Command::_loginNotFree()
{
	char *str;

	Buffer::getCmd(&str, 0, 230, "");
	return str;
}

char 	*Command::_noData()
{
	char *str;

	Buffer::getCmd(&str, 0, 231, "");
	return str;
}

char 	*Command::_loginNotMatching()
{
	char *str;

	Buffer::getCmd(&str, 0, 232, "");
	return str;
}

char 	*Command::_loginTooLong()
{
	char *str;

	Buffer::getCmd(&str, 0, 237, "");
	return str;
}

char 	*Command::_listLogin(Buff *_entry, User *user)
{
	if (_entry->size == 0)
		return _noData();

	std::string s((char *)_entry->data);
	std::string _logins;
	std::stringstream ss;

	for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
	{
		if ((*it)->getName().compare(s) == 0)
			return _loginNotFree();
	}

	user->setName(s);

	for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
	{
		ss << (*it)->getName() << "/";
	}
	_logins = ss.str();

	int size = _logins.size();
	char *str;

	std::cout << s << " / " << _logins << std::endl;

	Buffer::getCmd(&str, size, 103, _logins.c_str());
	return str;
}

char 	*Command::_getUserInfo(Buff *_entry, User *)
{
	if (_entry->size == 0)
		return _noData();

	std::string s((char *)_entry->data);
	std::size_t separator = s.find("/");
	std::string arg1 = s.substr(0, separator - 1);
	std::string arg2 = s.substr(separator + 1);

	for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
	{
		if ((*it)->getName().compare(arg2) == 0)
		{
			// do something
		}
	}

	return _loginNotMatching();

}

char 	*Command::analyse(char *str, User *user)
{
	Buff 	*_entry = new Buff();

	_entry = Buffer::getValue(str);

	// test
	std::cout << _entry->magic << " ";
	std::cout << (int)_entry->cmd << " ";
	std::cout << _entry->size << " ";
	std::cout << _entry->data << std::endl;

	if ((int)_entry->cmd <= 0)
		return NULL;
	switch ((int)_entry->cmd)
	{
		case 102:
			return _listLogin(_entry, user);
			break;
		case 111:
			return _getUserInfo(_entry, user);
			break;
		default:
			return _unknownCommand();
			break;
	}
}

char 	*Command::sayHello()
{
	char 	*str;

	Buffer::getCmd(&str, 5, 101, "Hello");
	return str;
}

void 	Command::setLogins(std::vector<User *> users)
{
	_users = users;
}