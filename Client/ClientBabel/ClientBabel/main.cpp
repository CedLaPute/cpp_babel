#include "window.h"
#include "ASocket.hh"
#include <QtWidgets/QApplication>

int main(int argc, char *av[])
{
	QApplication a(argc, av);

	ASocket *tmp;

	tmp = ASocket::getNewSocket((short)atoi(av[2]));
	tmp->Connect(av[1], (short)atoi(av[2]));
	tmp->Receive();
	/* y avait un sleep(5) ici*/

	window w;
	w.show();
	return a.exec();
}
