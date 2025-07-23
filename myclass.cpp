#include "myclass.h"


MyClass::MyClass(QObject *parent)
    : QObject{parent}, min_id(0), last_word("")
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
}

QString MyClass::getNextWord()
{
    if(last_id>=max_id)
        last_id=min_id;

    last_id++;
    last_word = m_db.searchTable("words","w_id",QString::number(last_id),"w_text");
    return last_word;
}


void MyClass::next(QString value)
{
    if(value == last_word)
        emit nextWordReady(getNextWord());
    else
        qInfo() << "incorrect value entered.";
}

MyClass::~MyClass()
{
    delete m_query;
}


// code drivers for datbase
// for(int i=0; i<=20; i++)
// {
//     QMap<QString, QVariant> data;
//     data["w_id"] = i;
//     data["w_text"] = "w_word word "+QString::number(i);
//     data["w_meaning"] = "w_meaning word "+QString::number(i);
//     data["w_example"] = "Tw_exampleest word "+QString::number(i);
//     data["w_in_persian"] = "w_in_persian word "+QString::number(i);
//     data["w_status"] = "w_status word "+QString::number(i);
//     data["w_source"] = "w_source word "+QString::number(i);
//     m_db.insertIntoTable("words", data);
// }


// db.updateTableValue("mytable", "name", "Alice", "age", 31);

// Search
// label_word->setText(m_db.searchTable("words","w_id","1","w_text"));


// Remove table
// db.removeTable("mytable");
