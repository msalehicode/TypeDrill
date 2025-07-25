#include "backend.h"

void Backend::wordIs()
{
    last_word.clear();
    last_word << m_db.searchTable("words", "w_id", QString::number(last_id), "w_text");
    last_word << m_db.searchTable("words", "w_id", QString::number(last_id), "w_meaning");
    last_word << m_db.searchTable("words", "w_id", QString::number(last_id), "w_example");
    qInfo() << last_word;
}

Backend::Backend(QObject *parent)
    : QObject{parent}, min_id(0)
{
    last_id=min_id;
    if(m_db.init("./database","practiceWords.sqlite"))
    {
        m_query = new QSqlQuery((*m_db.getDatabase()));
    }
    else
        qFatal() << "failed to init database..";

    max_id=m_db.countRows("words");
    qInfo() << "maxid=" << max_id << "\tminid=" << min_id;
    m_db.createTable("words", "w_id INTEGER PRIMARY KEY,\
                     w_text TEXT,\
                     w_meaning TEXT,\
                     w_example TEXT,\
                     w_in_persian TEXT,\
                     w_status TEXT,\
                     w_source TEXT"
                     );

    //to avoid empty QStringList.
    last_word << "";
}

void Backend::getNextWord(const QString &userText)
{
    if(last_id>=max_id)
        last_id=min_id;

    last_id++;

    if (last_word.size() > 0 && userText == last_word[0])
    {
        wordIs();
        qInfo() << "usertext= " << userText;
        qInfo() << "last_wrod=" << last_word;
        emit wordReady(last_word);
    }
    else
        qInfo() << "incorrect value entered.";
}

