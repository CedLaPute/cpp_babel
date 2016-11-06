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
  void			reset();
public:

  LinNetwork();
  virtual ~LinNetwork();

  virtual void		connection(std::string const, std::string const);
  virtual void		connectClient();

  virtual std::string	readIn();
  virtual void		writeOut(std::string const);

  virtual void		close();

  void			loop();
};

#endif /* !LINNETWORK_HH_ */
