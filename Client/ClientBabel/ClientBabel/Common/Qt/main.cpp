#include <iostream>

#include <QApplication>
#include "window.hh"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    window win;
    win.show();

    return app.exec();
}
