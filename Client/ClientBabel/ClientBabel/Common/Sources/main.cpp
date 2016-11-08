#include "../Headers/INetwork.hh"

#ifdef _WIN32
#include "../../Windows/Headers/WinNetwork.hh"

#elif __linux__
#include <LinNetwork.hh>
#endif

int	main(int , char **)
{
  #ifdef _WIN32
  	WinNetwork *tmp = new WinNetwork;
  #elif __linux__
    LinNetwork *tmp = new LinNetwork;
  #endif

  tmp->connection("2727", "10.14.58.115");

  while (1)
    {
      tmp->loop();
    }
  return 0;
}
