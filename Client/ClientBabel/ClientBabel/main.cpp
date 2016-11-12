#include "window.h"
#include <QApplication>

int main(int argc, char *av[])
{	
  QApplication a(argc, av);
  
  window w;
  w.show();
  return a.exec();
}
