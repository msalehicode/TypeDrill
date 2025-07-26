#include "backend.h"

void Backend::wordIs()
{
    last_word.clear();
    if(currentTableName[0]=='w')
    {
        last_word << m_db.searchTable(currentTableName, "w_id", QString::number(last_id), "w_text");
        last_word << m_db.searchTable(currentTableName, "w_id", QString::number(last_id), "w_meaning");
        last_word << m_db.searchTable(currentTableName, "w_id", QString::number(last_id), "w_example");
    }
    else if(currentTableName[0]=='v')
    {
        last_word << m_db.searchTable(currentTableName, "v_id", QString::number(last_id), "v_past");
        last_word << m_db.searchTable(currentTableName, "v_id", QString::number(last_id), "v_past");
        last_word << m_db.searchTable(currentTableName, "v_id", QString::number(last_id), "v_past_perfect");
    }
    else
    {
        //just to fill last word with somethinge
        last_word << "error, could not detect current table type.";
    }

    qInfo() <<"wordisresult:"<< last_word;
}

Backend::Backend(QObject *parent)
    : QObject{parent}, min_id(0)
{
    if(m_db.init("./database","practiceWords.sqlite"))
    {
        m_query = new QSqlQuery((*m_db.getDatabase()));
    }
    else
        qFatal() << "failed to init database..";


    m_db.createTable("user_tables", "t_id INTEGER PRIMARY KEY AUTOINCREMENT,\
                     t_title TEXT,\
                     t_status TEXT"
                     );






}

void Backend::getNextWord(const QString &userText)
{
    if(last_id>=max_id)
        last_id=min_id;

    last_id++;

    qInfo() <<"debuggg"<< last_word << "" << last_word[0];
    if (last_word.size() > 0 && userText == last_word[0])
    {
        wordIs();
        qInfo() << "usertext= " << userText;
        qInfo() << "last_wrod=" << last_word;
        qInfo() << "last id =" << last_id << "maxid="<<max_id<< "minud="<<min_id;
        emit wordReady(last_word);
    }
    else
        qInfo() << "incorrect value entered.";
}

void Backend::getTables()
{
    //fetch table from db
    QVariantList tables = m_db.getAllRowsAsVariantList("user_tables");
    qInfo() << tables;
    emit tablesList(tables);//return result
}

void Backend::createTable(const QString &tableName, const QString &tableType)
{
    QString result;
    if(tableType=="word")
    {
            bool qresult = m_db.createTable("w_"+tableName, "w_id INTEGER PRIMARY KEY AUTOINCREMENT,\
                             w_text TEXT,\
                             w_meaning TEXT,\
                             w_example TEXT,\
                             w_translate TEXT,\
                             w_status TEXT,\
                             w_source TEXT"
                             );
            if(qresult)
            {
                result="word table successfully created.";

                QMap<QString, QVariant> rowData;
                rowData["t_title"] = "w_"+tableName;
                rowData["t_status"] = "0";

                qresult = m_db.insertIntoTable("user_tables", rowData);
                if(qresult)
                    result+= " and added to user_tables.";
                else
                    result+= " but could not add to user_tables this will occure problem.";
            }
            else
                result="error: table word failed to create.";
    }
    else if(tableType=="verb")
    {
        bool qresult = m_db.createTable("v_"+tableName, "v_id INTEGER PRIMARY KEY AUTOINCREMENT,\
                                        v_verb TEXT,\
                                        v_past TEXT,\
                                        v_past_perfect TEXT,\
                                        v_status TEXT"
                                        );
        if(qresult)
        {
            result="verb table successfully created.";

            QMap<QString, QVariant> rowData;
            rowData["t_title"] = "v_"+tableName;
            rowData["t_status"] = "0";

            qresult = m_db.insertIntoTable("user_tables", rowData);
            if(qresult)
                result+= " and added to user_tables.";
            else
                result+= " but could not add to user_tables this will occure problem.";
        }
        else
            result="error: table verb failed to create.";
    }
    else
    {
        result="error: undefined table type.";
    }

    emit tableCreationResult(result);
}

void Backend::switchTable(const QString &tableName,const QString& tableId)
{
    resetPractice();
    currentTableName=tableName;
    currentTableId=tableId;

    qInfo()<< "table switched to user_table :" << currentTableName << " id:" << currentTableId;

    max_id=m_db.countRows(currentTableName);

    qInfo() << "maxid=" << max_id << "\tminid=" << min_id;
}

void Backend::whatIsCurrentTableType()
{
    QString result;
    if(currentTableName[0]=='w')
        result="word";
    else if(currentTableName[0]=='v')
        result="verb";
    else
        result="?";
    qInfo() << "current table type is :" << result;
    emit tableTypeIs(result);
}

void Backend::addWordToTable(const QStringList &data)
{
    qInfo()<< "adword to tbael";

    QString result;
    bool qresult;
    if(currentTableName[0]=='w' && data.size() >=6)
    {
        //data order passed by QML for word: text, meaning, example, translate, source, status
        QMap<QString, QVariant> rowData;
        rowData["w_text"] = data[0];
        rowData["w_meaning"] = data[1];
        rowData["w_example"] = data[2];
        rowData["w_translate"] = data[3];
        rowData["w_source"] = data[4];
        rowData["w_status"] = data[5];

        qresult = m_db.insertIntoTable(currentTableName, rowData);
        if(qresult)
            result= "word added to the table.";
        else
            result= "failed to add word into the table.";
    }
    else if(currentTableName[0]=='v' && data.size() >=4)
    {
        //data order passed by QML for verb: verb, past, past perfect, status
        QMap<QString, QVariant> rowData;
        rowData["v_verb"] = data[0];
        rowData["v_past"] = data[1];
        rowData["v_past_perfect"] = data[2];
        rowData["v_status"] = data[3];
        qresult = m_db.insertIntoTable(currentTableName, rowData);
        if(qresult)
            result= "verb added to the table.";
        else
            result= "failed to add verb into the table.";
    }
    else
    {
        qInfo() << "undefined table type or invalid parameters.";
        result="error, underined table type or invalid parameters";
    }

    emit addItemtoTableResult(result);
}

void Backend::resetPractice()
{
    last_id=min_id;
    last_word.clear();
    //to avoid empty QStringList.
    last_word << "";
    qInfo() << "practice reseted.";
}

