#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "myclass.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    MyClass* mclass;
    QLabel* label_word;
    QLineEdit* input_text;

    QVBoxLayout* layout;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
