#include "mytcpserver.h"
#include <QTcpSocket>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>

ClientHandler::ClientHandler(qintptr socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}

void ClientHandler::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

    qDebug() << "Client connected: " << socketDescriptor;

    if (!connectToDatabase()) {
        qDebug() << "Failed to connect to database.";
        return;
    }

    handleClient(tcpSocket);
    exec();
}

bool ClientHandler::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\obser\\Documents\\timp3\\server.db");

    if (!db.open()) {
        qDebug() << "Database error occurred: " << db.lastError().text();
        return false;
    }
    return true;
}

void ClientHandler::handleClient(QTcpSocket &tcpSocket)
{
    while (tcpSocket.state() == QAbstractSocket::ConnectedState) {
        if (tcpSocket.waitForReadyRead()) {
            QByteArray data = tcpSocket.readAll();
            qDebug() << "Received data:" << data;

            // Пример выполнения запроса к базе данных
            QString queryStr = "SELECT * FROM users";  // замените на ваш SQL-запрос
            executeQuery(queryStr);
        }
    }
}

void ClientHandler::executeQuery(const QString &queryStr)
{
    QSqlQuery query;
    if (!query.exec(queryStr)) {
        qDebug() << "SQL error occurred: " << query.lastError().text();
    } else {
        while (query.next()) {
            QString result = query.value(0).toString();  // Пример получения результата
            qDebug() << "Query result:" << result;
        }
    }
}

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer(parent)
{
}

MyTcpServer::~MyTcpServer()
{
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "Incoming connection: " << socketDescriptor;

    ClientHandler *clientHandler = new ClientHandler(socketDescriptor, this);
    connect(clientHandler, &ClientHandler::finished, clientHandler, &ClientHandler::deleteLater);
    clientHandler->start();
}

