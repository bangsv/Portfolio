#include "MainWindow.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[]){
    
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon("d:/Desktop/.A_Porgramm/Course_OOP_QT/labriory_curs/icon.png"));

    MainWindow w;
    w.setWindowTitle("Library");
    w.show();
    return a.exec();

}
