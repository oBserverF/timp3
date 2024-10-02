#include "database.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

Database* Database::m_instance = nullptr;

Database* Database::instance()
{
    if (!m_instance) {
        m_instance = new Database();
    }
    return m_instance;
}

Database::Database(QObject *parent)
    : QObject(parent)
{
    // Инициализация подключения к базе данных SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\obser\\Documents\\timp3\\server.db");
    // Проверка подключения к базе данных
    if (!db.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";

        // Пример создания таблицы, если она не существует
        //QSqlQuery query;
        //if (!query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, password TEXT)")) {
        //    qDebug() << "Failed to create table: " << query.lastError().text();
        //} else {
        //    qDebug() << "Table 'users' checked or created successfully.";
        //}
    }
}

Database::~Database()
{
    // Закрытие соединения с базой данных при уничтожении объекта
    db.close();
    qDebug() << "Database connection closed.";
}

void Database::handleRequest(const QByteArray &data)
{

    Database* db = new Database();
    db->instance();
    // Пример обработки запроса
    qDebug() << "Handling request: " << data;

    QSqlQuery query;
    QString command = QString(data);  // Преобразование данных в строку для обработки команд

    // Пример базовой логики для регистрации
    if (command.startsWith("reg")) {
        QStringList params = command.trimmed().split(" ");
        if (params.size() < 3) {
            qDebug() << "Error: Invalid registration command format";
            return;
        }

        QString name = params.at(1);
        QString password = params.at(2);

        query.prepare("INSERT INTO users (name, password) VALUES (:name, :password)");
        query.bindValue(":name", name);
        query.bindValue(":password", password);

        if (!query.exec()) {
            qDebug() << "Registration failed: " << query.lastError().text();
        } else {
            qDebug() << "User registered: " << name;
        }
    }
    // Пример базовой логики для авторизации
    else if (command.startsWith("login")) {
        QStringList params = command.trimmed().split(" ");
        if (params.size() < 3) {
            qDebug() << "Error: Invalid login command format";
            return;
        }

        QString name = params.at(1);
        QString password = params.at(2);

        query.prepare("SELECT * FROM users WHERE name = :name AND password = :password");
        query.bindValue(":name", name);
        query.bindValue(":password", password);

        if (!query.exec()) {
            qDebug() << "Login failed: " << query.lastError().text();
        } else if (!query.next()) {
            qDebug() << "Login failed: user not found or incorrect password";
        } else {
            qDebug() << "User logged in: " << name;
        }
    }
    // Обработка других команд
    else {
        qDebug() << "Unknown command: " << command;
    }
}
