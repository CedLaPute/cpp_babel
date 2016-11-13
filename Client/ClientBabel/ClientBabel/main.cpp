#include "window.h"
#include "Network.h"
#include <QApplication>

void	makeConnect(window *w, Network *n)
{
  QObject::connect(w, SIGNAL(newName(QString const &)), n, SLOT(newName(QString const &)));
  QObject::connect(w, SIGNAL(sndCall(QString const &)), n, SLOT(sndCall(QString const &)));
  QObject::connect(w, SIGNAL(acceptCall()), n, SLOT(acceptCall()));
  QObject::connect(w, SIGNAL(refuseCall()), n, SLOT(refuseCall()));
  QObject::connect(w, SIGNAL(endCall()), n, SLOT(endCall()));
  
  QObject::connect(n, SIGNAL(nameTaken()), w, SLOT(nameTaken()));
  QObject::connect(n, SIGNAL(sndFailed()), w, SLOT(sndFailed()));
  QObject::connect(n, SIGNAL(nameWrong()), w, SLOT(nameWrong()));
  QObject::connect(n, SIGNAL(unknownName()), w, SLOT(unknownName()));
  QObject::connect(n, SIGNAL(callFailed()), w, SLOT(callFailed()));
  QObject::connect(n, SIGNAL(connectFailed()), w, SLOT(connectFailed()));
}

int main(int argc, char *av[])
{	
  QApplication	a(argc, av);  
  window	w;
  Network	net;

  makeConnect(&w, &net);
  w.show();
  net.start();
  return a.exec();
}
