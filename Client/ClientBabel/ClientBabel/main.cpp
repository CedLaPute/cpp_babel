#include "window.h"
#include "Network.h"
#include <QApplication>

void	makeConnect(window *w, Network *n)
{
  //QThread	*t = new QThread();
  
  QObject::connect(w, SIGNAL(newName(QString)), n, SLOT(newName(QString)));
  QObject::connect(w, SIGNAL(sndCall(QString)), n, SLOT(sndCall(QString)));
  QObject::connect(w, SIGNAL(acceptCall()), n, SLOT(acceptCall()));
  QObject::connect(w, SIGNAL(refuseCall()), n, SLOT(refuseCall()));
  QObject::connect(w, SIGNAL(endCall()), n, SLOT(endCall()));
  
  QObject::connect(n, SIGNAL(nameTaken()), w, SLOT(nameTaken()));
  QObject::connect(n, SIGNAL(sndFailed()), w, SLOT(sndFailed()));
  QObject::connect(n, SIGNAL(nameWrong()), w, SLOT(nameWrong()));
  QObject::connect(n, SIGNAL(unknownName()), w, SLOT(unknownName()));
  QObject::connect(n, SIGNAL(callFailed()), w, SLOT(callFailed()));
  QObject::connect(n, SIGNAL(connectFailed()), w, SLOT(connectFailed()));
  QObject::connect(n, SIGNAL(listLogin(QLabel *), w, SLOT(listLogin(QLabel *))));

  n->start();

  //QObject::connect(t, SIGNAL(started()), n, SLOT(run()));

  //  n->moveToThread(t);
  //  t->exec();
}

int main(int argc, char *av[])
{	
  QApplication	a(argc, av);  
  window	w;
  Network	net;

  makeConnect(&w, &net);
  w.show();
  return a.exec();
}
