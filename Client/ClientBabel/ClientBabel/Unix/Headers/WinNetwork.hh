#ifndef WINNETWORK_HH_
# define WINNETWORK_HH_

# include <INetwork.hh>

class	WinNetwork : public INetwork
{
public:

  WinNetwork();
  virtual ~WinNetwork();
  
  virtual void		connection();
  virtual void		close();
  virtual std::string	readIn();
  virtual void		writeOut(std::string const);
};
  
#endif /* !WINNETWORK_HH_ */
