#include "helpwindow.h"
#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWindow){
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/MainPiNew.ico"));
    this->setWindowTitle("Course work");
}

HelpWindow::~HelpWindow()
{
    delete ui;
}
