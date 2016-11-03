#ifndef LINNETWORK_HH_
# define LINNETWORK_HH_

# include <INetwork.hh>

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

class	LinNetwork : public INetwork
{
private:
  int			_sock;
  std::string		_buff;
  
  fd_set		_fdRead;
  fd_set		_fdWrite;

  struct protoent	*_pe;
  struct sockaddr_in	_sIn;

  bool			init();
public:

  LinNetwork();
  virtual ~LinNetwork();

  virtual void		connection();
  virtual void		close();
  virtual std::string	read();
  virtual void		write(std::string const);
};

#endif /* !LINNETWORK_HH_ */
