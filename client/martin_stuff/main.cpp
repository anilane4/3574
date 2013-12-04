#include <QApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    client clientHi;
#ifdef Q_OS_SYMBIAN
    // Make application better looking and more usable on small screen
    client.showMaximized();
#else
    clientHi.show();
#endif
    return clientHi.exec();
}
