#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createnewfile.h"
#include "helpwindow.h"

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
#include <QTranslator>
#include <QTransform>

QString str_file;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    createnefile = new CreateNewFile();
    connect(this,&MainWindow::signalString, createnefile, &CreateNewFile::signalString);

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    QString str_file;
    str_file = QFileDialog::getOpenFileName(this,"Creat file","D:/Desktop/Qt/build-Cyrsach-Desktop_Qt_5_7_0_MinGW_32bit-Debug/File for encrypt","All Files (*.txt);; BIN (*.bin)");
    ui->label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->label->setText(str_file);

    strFileData = str_file;

    emit signalString(str_file);
    if(str_file.size() != 0){
        createnefile->show();
    } else if(str_file.size() == 0){
        ui->label->setText("File not selected");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    str_file = QFileDialog::getOpenFileName(this,"Creat file","D:/Desktop/Qt/build-Cyrsach-Desktop_Qt_5_7_0_MinGW_32bit-Debug/File for encrypt","All Files (*.txt);; BIN (*.bin)");
    ui->label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->label->setText(str_file);

    strFileData = str_file;

    if(strFileData.size() == 0){
        ui->label->setText("File not opened/Not selected");
    }
}

void MainWindow::on_pushButton_3_clicked(){
    strFileData.clear();
    readisFile.clear();
    ui->label->setText("Selected file / Data from file");
}

void MainWindow::on_pushButton_4_clicked(){

    if(ui->label->text() == "Selected file / Data from file"){
         ui->label->setText("File not selected");
    } else if(ui->label->text() != "Selected file / Data from file"){
          QFile file(strFileData);
          if(file.open(QIODevice::ReadOnly)){
              readisFile = file.readAll();
              qDebug() << readisFile;
              ui->label->setText(readisFile);
              file.close();
          }
    }
}


void MainWindow::on_comboBox_activated(const QString &arg1){
    ui->label_2->setTextInteractionFlags(Qt::TextSelectableByMouse);
    Combobox = arg1;
    if(arg1 == "Choose the desired cipher"){
        Combobox = "0";
    }

    if(arg1 == "Vernam cipher"){
        ui->label_2->setText("A cipher is a type of one-time pad cryptosystem. It uses the Boolean XOR function.\nThe Vernam cipher is an example of a system with absolute cryptographic strength.\nAt the same time, it is considered one of the simplest cryptosystems.");
        Combobox = "Vernam cipher";
    }

    if(arg1 == "Caesar's cipher"){
        ui->label_2->setText("A Caesar cipher, also known as a shift cipher, a Caesar code is one of the simplest and\nmost widely used detection methods.A Caesar cipher is a type of substitution cipher\nin which each character in a text operation is replaced by a character that finds\nat a constantinclusion of positions to the left or right of it in alphabet.\nFor example, in a cipher with a case on the right of 3,A was replaced by D, B became D,\nand so on. The cipher is named after the Roman general Gaius Julius Caesar,who used it for\nsecret correspondence with his generals. The action step implemented by the\n Caesar cipher,often included as part of a more complex scheme such as the Vigenère cipher.");
    }
}

void MainWindow::on_pushButton_5_clicked(){
      if(Combobox == "0" ||Combobox ==""){
        ui->label_2->setText("No cipher selected");
       }


      if(readisFile.size() == 0){
         ui->label_2->setText("File not selected");
      } else if(readisFile.size() > 0){
          if(Combobox == "Vernam cipher"){
                  VernamSelect();
          }
          if(Combobox == "Caesar's cipher"){
              CaesarCipherEncd();
          }
      }
}

void MainWindow::on_pushButton_7_clicked(){
     ui->label_4->setTextInteractionFlags(Qt::TextSelectableByMouse);
     str_file = QFileDialog::getOpenFileName(this,"Creat file","D:/Desktop/Qt/build-Cyrsach-Desktop_Qt_5_7_0_MinGW_32bit-Debug/File for encrypt","All Files (*.txt);; BIN (*.bin)");
     ui->label_4->setText(str_file);

     QFile file(str_file);
     if(file.open(QIODevice::ReadOnly)){
         keyAll = file.readAll();
         qDebug() << keyAll;
         file.close();
     }

}

void MainWindow::on_pushButton_8_clicked(){
    ui->label_5->setTextInteractionFlags(Qt::TextSelectableByMouse);
    str_file = QFileDialog::getOpenFileName(this,"Creat file","D:/Desktop/Qt/build-Cyrsach-Desktop_Qt_5_7_0_MinGW_32bit-Debug/File for encrypt","All Files (*.txt);; BIN (*.bin)");
    ui->label_5->setText(str_file);

    QFile file(str_file);
    if(file.open(QIODevice::ReadOnly)) {
        EncondingStrAll = file.readAll();
        qDebug() << EncondingStrAll;
        file.close();
    }

}

void MainWindow::on_comboBox_2_activated(const QString &arg1){
    ui->label_3->setTextInteractionFlags(Qt::TextSelectableByMouse);
    Combobox = arg1;
    if(arg1 == "Choose the right decoder"){
        Combobox = "0";
    }

    if(arg1 == "Vernam cipher"){
        Combobox = "Vernam cipher";
    }

    if(arg1 == "Caesar's cipher"){
        Combobox = "Caesar's cipher";
    }

}

void MainWindow::on_pushButton_6_clicked(){ // Decipher Button
    if(Combobox == "0" ||Combobox ==""){
      ui->label_2->setText("No decipher selected");
     }

    if(Combobox == "Vernam cipher"){
        DecryptionVernam();
    }

    if(Combobox == "Caesar's cipher"){
        CaesarCipherDecrypt();
    }
}

void MainWindow::on_actionCreate_file_triggered(){
    QString str_file;
    str_file = QFileDialog::getOpenFileName(this,"Creat file","D:/Desktop/Qt/build-Cyrsach-Desktop_Qt_5_7_0_MinGW_32bit-Debug/File for encrypt","All Files (*.txt);; BIN (*.bin)");
    ui->label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->label->setText(str_file);

    strFileData = str_file;

    emit signalString(str_file);
    if(str_file.size() != 0){
        createnefile->show();
    } else if(str_file.size() == 0){
        ui->label->setText("File not selected");
    }
}

void MainWindow::on_actionOpen_file_triggered(){
    str_file = QFileDialog::getOpenFileName(this,"Creat file","D:/Desktop/Qt/build-Cyrsach-Desktop_Qt_5_7_0_MinGW_32bit-Debug/File for encrypt","All Files (*.txt);; BIN (*.bin)");
    ui->label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->label->setText(str_file);

    strFileData = str_file;
    if(strFileData.size() == 0){
        ui->label->setText("File not opened/Not selected");
    }

}

void MainWindow::on_actionClose_triggered(){
    QApplication::quit();
    qApp->quit();

}

void MainWindow::on_actionRussian_triggered(){
    QTranslator translator;

    translator.load("QtLanguage_ru");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

void MainWindow::on_actionEnglish_triggered(){
    QTranslator translator;
    translator.load("QtLanguage_en");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

void MainWindow::on_actionAbout_the_program_triggered(){
    aboutprog = new AboutProgramm;
    aboutprog->show();
}

void MainWindow::on_actionHelp_2_triggered(){
    helpwin = new HelpWindow;
    helpwin->show();
}

void randomkey(QString& key,QString Alphabet){
    for (int i = 0; i < key.size(); i++) {
        key[i] = Alphabet[1 + rand() % Alphabet.length()];
    }
}

QString operator ^ (const QString& str, const QString& key){
    QString result;
    for(int i = 0; i < str.size(); i++)
        result.append(QString(QChar(str[i]).unicode() ^ QChar(key[i]).unicode()));
    return result;
}

void MainWindow::VernamSelect(){

    QString Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$(%)*-+1234567890";

    QString key;
    key.resize(readisFile.size());
    randomkey(key,Alphabet);

    QString filename = "KeyVernam.txt";
    QFile fileKey(filename);
    bool openOk = fileKey.open(QIODevice::ReadWrite);
    if (openOk){
        QTextStream out(&fileKey);
        out << key;
        fileKey.close();
    }

    QString strIsFile = readisFile;
    QString Encodingstring;

    Encodingstring = strIsFile ^ key;

    QString filenameEnc = "EncodingTextVernam.txt";
    QFile fileEnc(filenameEnc);
    bool openOkEnc = fileEnc.open(QIODevice::ReadWrite);
    if (openOkEnc){
        QTextStream out(&fileEnc);
        out << Encodingstring;
        fileEnc.close();
        ui->label_2->setText("Encryption was successful\nHere is a description of the selected cipher");
    }
}

void MainWindow::DecryptionVernam(){

    QString key = keyAll;
    QString encodingText = EncondingStrAll;

    QString DencTextSTR;
    DencTextSTR = key ^ encodingText;

    ui->label_3->setText(DencTextSTR);

    if(DencTextSTR.size() < 2){
        ui->label_3->setText("The file cannot be decrypted.\nCheck files for decryption");
    }

    else if(DencTextSTR.size() > 1){
        QString filenameDecip = "DecipherTextVernam.txt";
        QFile fileDecip(filenameDecip);
        bool openOkDEnc = fileDecip.open(QIODevice::ReadWrite);
        if (openOkDEnc){
            QTextStream out(&fileDecip);
            out << DencTextSTR;
            fileDecip.close();

            QString OutputString = "Decryption was successful\nMessage from file: " + DencTextSTR;
            ui->label_3->setText(OutputString);

        }
    }
}



void MainWindow::CaesarCipherEncd(){
    QString strstring = readisFile;
    int randNumber = rand()% 5 + 1;

    QString filename = "KeyCaesar.txt";
    QFile fileKey(filename);

    bool openOk = fileKey.open(QIODevice::ReadWrite);

    if (openOk){
        QTextStream out(&fileKey);
        out << randNumber;
        fileKey.close();
    }

    for(int i = 0; i < strstring.size();i++)
        strstring[i].unicode() += randNumber;

    QString filenameEnc = "EncodingTextCaesar.txt";
    QFile fileEnc(filenameEnc);
    bool openOkEnc = fileEnc.open(QIODevice::ReadWrite);
    if (openOkEnc){
        QTextStream out(&fileEnc);
        out << strstring;
        fileEnc.close();
        ui->label_2->setText("Encryption was successful\nHere is a description of the selected cipher");
    }
}

void MainWindow::CaesarCipherDecrypt(){

    QString key = keyAll;
    int keyInt = key.toInt();

    QString encodingText = EncondingStrAll;

    for(int i = 0; i < encodingText.size();i++)
         encodingText[i].unicode() -= keyInt;

    if(encodingText.size() < 2)
        ui->label_3->setText("The file cannot be decrypted.\nCheck files for decryption");


    else if(encodingText.size() > 1){
        QString filenameDecip = "DecipherTextCaesar.txt";
        QFile fileDecip(filenameDecip);
        bool openOkDEnc = fileDecip.open(QIODevice::ReadWrite);
        if (openOkDEnc){

            QTextStream out(&fileDecip);
            out << encodingText;
            fileDecip.close();

            QString OutputString = "Decryption was successful\nMessage from file: " + encodingText;
            ui->label_3->setText(OutputString);

        }
    }
}
