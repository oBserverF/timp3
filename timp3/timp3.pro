QT       += core network sql

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
           mytcpserver.cpp \
           database.cpp

HEADERS += mytcpserver.h \
           database.h

# Укажите путь к заголовочным файлам SQLite3
INCLUDEPATH += C:/sqlite3

# Укажите путь к библиотеке SQLite3
LIBS += -LC:/sqlite3 -lsqlite3


QT += sql
