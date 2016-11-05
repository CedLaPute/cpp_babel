#include <INetwork.hh>
#include <LinNetwork.hh>

int	main(int, char **)
{
  LinNetwork	*tmp = new LinNetwork;

  tmp->connection();

  while (1)
    tmp->loop();
  return 0;
}
