#include <LinNetwork.hh>
#include <iostream>
#include <string.h>
#include <unistd.h>

LinNetwork::LinNetwork()
{
  init();
}

LinNetwork::~LinNetwork()
{
}

bool		LinNetwork::init()
{
  if ((_pe = getprotobyname("TCP")) == NULL)
    return false;
  if ((_sock = socket(AF_INET, SOCK_STREAM, _pe->p_proto)) == -1)
    return false;
  return true;
}

void		LinNetwork::connection()
{
  _sIn.sin_family = AF_INET;
  _sIn.sin_port = htons(2727);
  _sIn.sin_addr.s_addr = inet_addr("192.168.1.91");

  if (connect(_sock, (struct sockaddr *)&(_sIn), sizeof(_sIn)) == -1)
    {
      _sock = -1;
      return ;
    }

  std::cout << "connected to server" << std::endl;
  return ;
}

void		LinNetwork::reset()
{
  FD_ZERO(&_fdWrite);
  FD_ZERO(&_fdRead);

  if (_sock != -1)
    {
      FD_SET(_sock, &_fdWrite);
      FD_SET(_sock, &_fdRead);
    }  
}

void		LinNetwork::loop()
{
  reset();

  if (select(_sock + 1, &_fdRead, &_fdWrite, NULL, NULL) == -1)
    return ;

  if (FD_ISSET(_sock, &_fdRead))
    if (readIn() != "")
      writeOut("94 C LE BARCA");
}

void		LinNetwork::close()
{
}

std::string	LinNetwork::readIn()
{
  std::string	res;
  char		buff[44000];
  int		i = 44000;

  while (buff[i] != '\0')
    {
      memset(buff, '\0', 44000);
      if ((i = read(_sock, buff, 44000 - 1)) <= 0)
	return "";

      std::string	t(buff);
      res = t;
    }
  std::cout << res << std::endl;
  return res;
}

void		LinNetwork::writeOut(std::string const str)
{
  if (_sock != -1)
    write(_sock, str.c_str(), 44000);
}
