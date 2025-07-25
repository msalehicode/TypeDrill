#include "myclass.h"

MyClass::MyClass(QObject *parent)
    : QObject{parent}
{}

QString MyClass::getNextWord()
{
    QString word = "example"; // fetch from DB or logic
    emit wordReady(word);
    return word;
}
