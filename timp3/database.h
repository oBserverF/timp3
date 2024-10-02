#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class Database : public QObject
{
    Q_OBJECT

public:
    static Database* instance();
    void handleRequest(const QByteArray &data);

private:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    // Методы для регистрации и авторизации
    void handleRegistration(const QString &username, const QString &password);
    void handleAuthentication(const QString &username, const QString &password);

    QSqlDatabase db;
    static Database *m_instance;
};

#endif // DATABASE_H
