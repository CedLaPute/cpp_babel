#include <LinNetwork.hh>

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
  
  _sIn.sin_family = AF_INET;
  _sIn.sin_port = htons(2727);
  _sIn.sin_addr.s_addr = inet_addr("192.168.1.91");

  if (connect(_sock, (struct sockaddr *)&(_sIn), sizeof(_sIn)) == -1)
    {
      _sock = -1;
      return false;
    }
  return true;
}

void		LinNetwork::connection()
{
}

void		LinNetwork::close()
{
}

std::string	LinNetwork::read()
{
  return "fdp";
}

void		LinNetwork::write(std::string const)
{
}
