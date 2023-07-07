#ifndef ABOUTPROGRAMM_H
#define ABOUTPROGRAMM_H

#include <QWidget>

namespace Ui {
class AboutProgramm;
}

class AboutProgramm : public QWidget
{
    Q_OBJECT

public:
    explicit AboutProgramm(QWidget *parent = 0);
    ~AboutProgramm();

private:
    Ui::AboutProgramm *ui;
};

#endif // ABOUTPROGRAMM_H
