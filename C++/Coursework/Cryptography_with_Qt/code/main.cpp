#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowTitle("Course work");
    w.setWindowIcon(QIcon(":/img/MainPiNew.png"));

    w.show();

    return a.exec();
}
