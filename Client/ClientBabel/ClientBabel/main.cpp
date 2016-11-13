#include "window.h"
#include "Network.h"
#include <QApplication>

int main(int argc, char *av[])
{	
  QApplication a(argc, av);
  
  window w;

  Network	*net = new Network();
  
  QObject::connect(&w, SIGNAL(sndName(QString const &)), net, SLOT(rcvName(QString const &)));
  QObject::connect(net, SIGNAL(sig(QString const &)), &w, SLOT(sig(QString const &)));
  w.show();
  net->start();
  return a.exec();
}
