#include "aboutprogramm.h"
#include "ui_aboutprogramm.h"

AboutProgramm::AboutProgramm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutProgramm){
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/MainPiNew.ico"));
    this->setWindowTitle("Course work");
}

AboutProgramm::~AboutProgramm(){
    delete ui;
}
