#ifndef WINNETWORK_HH_
# define WINNETWORK_HH_

# include "../../Common/Headers/INetwork.hh"
# include <string>

class	WinNetwork : public INetwork
{
public:

  WinNetwork();
  virtual ~WinNetwork();
  
  virtual void		connection(std::string const, std::string const);
  virtual void		connectClient();

  virtual std::string	readIn();
  virtual void		writeOut(std::string const);

  virtual void		close();
};
  
#endif /* !WINNETWORK_HH_ */
