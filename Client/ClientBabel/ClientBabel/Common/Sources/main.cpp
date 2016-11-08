#include <INetwork.hh>

#ifdef _WIN32
#include <WinNetwork.hh>

#elif __linux__
#include <LinNetwork.hh>
#endif

int	main(int , char **)
{
  LinNetwork	*tmp = new LinNetwork;

  tmp->connection("2828", "10.14.58.115");

  while (1)
    {
      tmp->loop();
    }
  return 0;
}
