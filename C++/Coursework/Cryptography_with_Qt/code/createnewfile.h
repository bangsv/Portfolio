#ifndef CREATENEWFILE_H
#define CREATENEWFILE_H

#include <QWidget>

namespace Ui {
class CreateNewFile;
}

class CreateNewFile : public QWidget
{
    Q_OBJECT

public:
    explicit CreateNewFile(QWidget *parent = 0);
    ~CreateNewFile();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public slots:
    void signalString(QString str_file);

private:
    Ui::CreateNewFile *ui;
    QString transfer;
};

#endif // CREATENEWFILE_H
