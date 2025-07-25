#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "database.h"
class Backend : public QObject
{
    Q_OBJECT
    DataBase m_db;

    void wordIs();

public:
    explicit Backend(QObject *parent = nullptr);
    Q_INVOKABLE void getNextWord(const QString& userText); // Call from QML

    QSqlQuery* m_query;
    // QString m_queryStr;
    int min_id;
    int max_id;
    int last_id;
    QStringList last_word;

signals:
    void wordReady(const QStringList &word);  // Emit to QML

};

#endif // BACKEND_H
