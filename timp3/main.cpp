#include <QCoreApplication>
#include "mytcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer server;
    if (!server.listen(QHostAddress::Any, 22222)) {
        qFatal("Failed to start server: %s", qPrintable(server.errorString()));
        return 1;
    }

    return a.exec();
}
