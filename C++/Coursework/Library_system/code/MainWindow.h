#pragma once

#include <QtWidgets/QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include "ui_MainWindow.h"

#include "Library.h"
#include "RentBooksBuilder.h"

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); 

private:
    Ui::MainWindowClass ui;
	Library library;
    void drow(QTableWidget* table);
    void drowUsers(QTableWidget* table);
    void drowReaders(QTableWidget* table);
    void drowrentBookUser(QTableWidget* table);
    void drowRentBooksTableLibr(QTableWidget* table);
    void filterAndDraw(QTableWidget* table, QString genre, QString title, QString author, QString year, QString pages);

    void Alldrow();

private slots:
    void on_pushButton_add_book_clicked();
    void on_pushButton_deleted_book_clicked();
	void on_pushButton_rent_book_clicked();
    
    void on_pushButton_input_acc_clicked();
    void on_pushButton_reg_acc_clicked();
    
    void on_pushButton_reg_acc_reader_clicked();
    void on_pushButton_input_acc_reader_clicked();

    void on_pushButton_filter_book_redear_clicked();
    void on_pushButton_reset_filter_reader_clicked();

    void on_pushButton_return_book_clicked();
    
    void on_pushButton_filter_book_clicked();
    void on_pushButton_reset_filter_clicked();

    bool showCheckBox_reader(std::string messang);
    bool showCheckBox_librarian(std::string messang);

};
