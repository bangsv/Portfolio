#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <createnewfile.h>
#include <aboutprogramm.h>
#include <helpwindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void VernamSelect();

    void CaesarCipherEncd();

    void CaesarCipherDecrypt();

    void DecryptionVernam();

    void on_actionCreate_file_triggered();

    void on_actionOpen_file_triggered();

    void on_actionClose_triggered();


    void on_actionRussian_triggered();

    void on_actionEnglish_triggered();

    void on_actionAbout_the_program_triggered();

    void on_actionHelp_2_triggered();

private:
    Ui::MainWindow *ui;
    CreateNewFile *createnefile;
    AboutProgramm *aboutprog;
    HelpWindow *helpwin;

    QString strFileData;//Передеча данных с файла в другую фукнцию
    QString readisFile; //Передеча путя файла в другую фукнцию
    QString keyAll;//Передеча ключа в другую фукнцию
    QString EncondingStrAll; //Передеча зашифр сообщения в другую фукнцию
    QString decstr;
    QString Combobox; //Для опредления какой шифр выбрать из Бокса


signals:
    void signalString(QString str_file);

};

#endif // MAINWINDOW_H
