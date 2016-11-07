//
// Created by lemonti on 11/3/16.
//

#ifndef CPP_BABEL_AUSER_HH
#define CPP_BABEL_AUSER_HH

# include <string>
# include <vector>

class AUser
{
  public:
	virtual ~AUser();
	std::string 		getName() const;
	void 				setName(const std::string name);
	int 				addContact(const std::string contact);

  protected:
	std::string					_name;
	std::vector<std::string>	_contactList;
};


#endif //CPP_BABEL_USER_HH
