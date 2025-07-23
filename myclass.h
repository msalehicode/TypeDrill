#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "database.h"

class MyClass : public QObject
{
    Q_OBJECT

public:
    explicit MyClass(QObject *parent = nullptr);
    DataBase m_db;
    QSqlQuery* m_query;
    QString m_queryStr;
    int min_id;
    int max_id;
    int last_id;
    QString last_word;
    QString getNextWord();
    ~MyClass();
public slots:
    void next(QString value);
signals:
    void nextWordReady(const QString& text);

};

#endif // MYCLASS_H
