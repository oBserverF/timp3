#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class ClientHandler : public QThread
{
    Q_OBJECT
public:
    explicit ClientHandler(qintptr socketDescriptor, QObject *parent = nullptr);
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    qintptr socketDescriptor;
    void handleClient(QTcpSocket &tcpSocket);
    bool connectToDatabase();
    void executeQuery(const QString &queryStr);
    QSqlDatabase db;
};

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // MYTCPSERVER_H

