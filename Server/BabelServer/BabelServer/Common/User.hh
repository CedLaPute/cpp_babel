//
// Created by lemonti on 11/3/16.
//

#ifndef CPP_BABEL_USER_HH
#define CPP_BABEL_USER_HH

# include <string>
# include <vector>

class User
{
  public:
	User();
	User(int fd);
	User(int fd, const std::string name);
	~User();
	std::string 		getName() const;
	void 				setName(const std::string name);
	int 				getFD() const;
	void 				setFD(int fd);
	int 				addContact(const std::string contact);


  private:
	std::string					_name;
	int							_fd;
	std::vector<std::string>	_contactList;
};


#endif //CPP_BABEL_USER_HH
