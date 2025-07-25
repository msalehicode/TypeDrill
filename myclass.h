#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>

class MyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr);

    Q_INVOKABLE QString getNextWord(); // Call from QML

signals:
    void wordReady(const QString &word);  // Emit to QML
};

#endif // MYCLASS_H
