#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    label_word = new QLabel(this);
    label_word->setText("");
    QFont font = label_word->font();
    font.setPointSize(35);
    label_word->setFont(font);

    input_text = new QLineEdit(this);
    input_text->setText("");
    input_text->setFont(font);


    // Create a vertical layout
    layout = new QVBoxLayout();
    layout->addWidget(label_word, 0, Qt::AlignHCenter);
    layout->addWidget(input_text, 0, Qt::AlignHCenter);
    QWidget* central = new QWidget(this);
    central->setLayout(layout);
    setCentralWidget(central);



    mclass = new MyClass(this);

    // connect(input_text, &QLineEdit::returnPressed, mclass, &MyClass::next);
    connect(input_text, &QLineEdit::returnPressed, [this](){
        mclass->next(input_text->text());
    });


    connect(mclass, &MyClass::nextWordReady, input_text, &QLineEdit::clear);
    connect(mclass, &MyClass::nextWordReady, label_word ,&QLabel::setText);


    //to make fetch data from database. its like initial
    mclass->next("");
}

MainWindow::~MainWindow()
{
    delete ui;
}
