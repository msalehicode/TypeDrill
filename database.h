#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

//SQL include
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlError>

//include File and Directory option
#include <QFile>
#include <QDir>

#include <QDebug>


#include <QVariant>
#include <QMap>
#include <QList>
#include <QSqlRecord>

class DataBase : public QObject
{
    Q_OBJECT

    QSqlDatabase* m_db;

    bool isDbExists(const QString& path, const QString& fileName);

public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
    bool init(const QString& path, const QString& fileName);
    QSqlDatabase *getDatabase();


    bool createTable(const QString& tableName, const QString& schema);
    bool removeTable(const QString& tableName);

    bool insertIntoTable(const QString& tableName, const QMap<QString, QVariant>& data);
    bool updateTableValue(const QString& tableName, const QString& keyColumn, const QVariant& keyValue,
                          const QString& updateColumn, const QVariant& updateValue);
    QList<QMap<QString, QVariant>> searchTable(const QString& tableName, const QString& columnName,
                                               const QVariant& searchValue);
    QString searchTable(const QString& tableName,const QString& columnName, const QString& searchValue,
                        const QString& columnYouWant);
    QVariantList getAllRowsAsVariantList(const QString& tableName);

    int countRows(const QString& tableName);

signals:
};
#endif // DATABASE_H
