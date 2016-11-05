#ifndef INETWORK_HH_
# define INETWORK_HH_

# include <string>

class	INetwork
{
public:
  virtual		~INetwork() {}

  virtual void		connection() = 0;
  virtual void		close() = 0;
  virtual std::string	readIn() = 0;
  virtual void		writeOut(std::string const) = 0;
};

# endif /* !INETWORK_HH_ */
