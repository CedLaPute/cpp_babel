#include <INetwork.hh>
#include <LinNetwork.hh>

int	main(int , char **)
{
  LinNetwork	*tmp = new LinNetwork;

  tmp->connection("2727", "192.168.1.91");

  while (1)
    {
      tmp->loop();
    }
  return 0;
}
