#include "createnewfile.h"
#include "ui_createnewfile.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QProcess>
#include <QMessageBox>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include <QFileDialog>
#include <QTextStream>
#include <QIODevice>
#include <Windows.h>

CreateNewFile::CreateNewFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateNewFile){
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/MainPiNew.ico"));
    this->setWindowTitle("Course work");

}

CreateNewFile::~CreateNewFile()
{
    delete ui;
}

void CreateNewFile::on_pushButton_clicked(){
    QFile file(transfer);

    QString str_input = ui->str_input->text();

    QMessageBox msgBox;

    if(str_input.size() == 0){
         msgBox.setWindowTitle("Notification");
         msgBox.setText("String contains no characters");
         msgBox.exec();
    } else if(str_input.size() > 0){
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
             QTextStream out(&file);
             out << str_input;
             file.close();
             ui->label->setText("Text written successfully");
        }
    }
}

void CreateNewFile::signalString(QString str_file){
    transfer = str_file;
}

void CreateNewFile::on_pushButton_2_clicked(){
      hide();
}
