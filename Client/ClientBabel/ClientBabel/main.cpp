#include "window.h"
#include "ASocket.hh"
#include "SocketManager.hh"
#include <QApplication>

int main(int argc, char *av[])
{
	try
	{
		SocketManager manager(av[1], (short)atoi(av[2]));

		while (manager.Select() != -1)
		{
			manager.handleReceive();
		}
	}
	catch (std::string const &err)
	{
		std::cerr << err << std::endl;
	}

	QApplication a(argc, av);

	window w;
	w.show();
	return a.exec();
}