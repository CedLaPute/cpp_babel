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
  virtual std::string	read();
  virtual void		write(std::string const);
};
  
#endif /* !WINNETWORK_HH_ */
