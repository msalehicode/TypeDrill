#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent} , m_db(nullptr)
{

}

DataBase::~DataBase()
{
    m_db->close();
    delete m_db;
}

bool DataBase::init(const QString &path, const QString &fileName)
{
    bool result=false;
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));


    QString fullPath = path+"/"+fileName;
    m_db->setDatabaseName(fullPath);

    if(QFile::exists(fullPath))
    {
        qInfo() << "databae exists, we will trying to open it.";
        if(m_db->open())
            result=true;
    }
    else
    {
        QDir dbDire(path);
        dbDire.mkpath(".");
        QFile dbFile(fullPath);
        if(m_db->open())
        {
            QSqlQuery createTable(*m_db);  // pass the opened database connection
            QString sql("CREATE TABLE settings\
            (\
              id INTEGER PRIMARY KEY,\
              theme_mode TEXT\
            );");
            createTable.prepare(sql);

            if(createTable.exec())
            {
                qInfo() << "database not found, we have been made one for you.";
                result=true;
            }
            else
            {
                qInfo() << "database creation exec failed.";//createTable.lastError().text();
                result=false;
            }

        }
        else
        {
            qInfo() << "m_db could not open database file.";
            result=false;
        }
    }
    return result;
}

QSqlDatabase *DataBase::getDatabase()
{
    return m_db;
}


// Create a table with a given schema (columns and types)
bool DataBase::createTable(const QString& tableName, const QString& schema)
{
    if (!m_db || !m_db->isOpen()) return false;

    QSqlQuery query(*m_db);
    QString sql = QString("CREATE TABLE IF NOT EXISTS %1 (%2);").arg(tableName, schema);

    if(!query.exec(sql))
    {
        qWarning() << "Create table failed:" << query.lastError().text();
        return false;
    }
    return true;
}

// Remove (drop) a table
bool DataBase::removeTable(const QString& tableName)
{
    if (!m_db || !m_db->isOpen()) return false;

    QSqlQuery query(*m_db);
    QString sql = QString("DROP TABLE IF EXISTS %1;").arg(tableName);

    if(!query.exec(sql))
    {
        qWarning() << "Remove table failed:" << query.lastError().text();
        return false;
    }
    return true;
}

// Insert into table - data map keys are column names, values are column values
bool DataBase::insertIntoTable(const QString& tableName, const QMap<QString, QVariant>& data)
{
    if (!m_db || !m_db->isOpen()) return false;
    if (data.isEmpty()) return false;

    QStringList columns = data.keys();
    QStringList placeholders;
    for (const auto& col : columns)
        placeholders << ":" + col;

    QString sql = QString("INSERT INTO %1 (%2) VALUES (%3);")
                      .arg(tableName)
                      .arg(columns.join(", "))
                      .arg(placeholders.join(", "));

    QSqlQuery query(*m_db);
    query.prepare(sql);

    for (auto it = data.constBegin(); it != data.constEnd(); ++it)
        query.bindValue(":" + it.key(), it.value());

    if (!query.exec())
    {
        qWarning() << "Insert failed:" << query.lastError().text();
        return false;
    }
    return true;
}

// Update value in table - update one column for a row identified by keyColumn = keyValue
bool DataBase::updateTableValue(const QString& tableName, const QString& keyColumn, const QVariant& keyValue,
                                const QString& updateColumn, const QVariant& updateValue)
{
    if (!m_db || !m_db->isOpen()) return false;

    QString sql = QString("UPDATE %1 SET %2 = :updateVal WHERE %3 = :keyVal;")
                      .arg(tableName, updateColumn, keyColumn);

    QSqlQuery query(*m_db);
    query.prepare(sql);

    query.bindValue(":updateVal", updateValue);
    query.bindValue(":keyVal", keyValue);

    if (!query.exec())
    {
        qWarning() << "Update failed:" << query.lastError().text();
        return false;
    }
    return true;
}

// Search table where columnName matches searchValue, returns list of maps with column-value pairs
QList<QMap<QString, QVariant>> DataBase::searchTable(const QString& tableName, const QString& columnName,
                                                     const QVariant& searchValue)
{
    QList<QMap<QString, QVariant>> results;
    if (!m_db || !m_db->isOpen()) return results;

    QString sql = QString("SELECT * FROM %1 WHERE %2 = :searchVal;").arg(tableName, columnName);

    QSqlQuery query(*m_db);
    query.prepare(sql);
    query.bindValue(":searchVal", searchValue);

    if (!query.exec())
    {
        qWarning() << "Search failed:" << query.lastError().text();
        return results;
    }

    while (query.next())
    {
        QMap<QString, QVariant> row;
        QSqlRecord record = query.record();
        for (int i = 0; i < record.count(); ++i)
        {
            row.insert(record.fieldName(i), query.value(i));
        }
        results.append(row);
    }
    return results;
}

QString DataBase::searchTable(const QString &tableName, const QString &columnName,
                              const QString &searchValue, const QString &columnYouWant)
{
    auto results = searchTable(tableName, columnName, searchValue);
    for (const auto& row : results)
    {
        return row.value(columnYouWant).toString();
    }
    return "";
}

int DataBase::countRows(const QString& tableName)
{
    if (!m_db || !m_db->isOpen()) {
        qWarning() << "Database is not open!";
        return -1;  // or 0, or some error code
    }

    QSqlQuery query(*m_db);
    QString sql = QString("SELECT COUNT(*) FROM %1").arg(tableName);

    if (!query.exec(sql)) {
        qWarning() << "Count query failed:" << query.lastError().text();
        return -1;
    }

    if (query.next()) {
        return query.value(0).toInt();
    }

    return 0;
}


