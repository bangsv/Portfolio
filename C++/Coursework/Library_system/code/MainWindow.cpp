#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {

	ui.setupUi(this);

	library.readBooksFromFile("databasy_books.txt");
	library.readUsersFromFile("databasy_users.txt");
	library.readReaderFromFile();
	library.distribution_readers();


	ui.lineEdit_input_password->setEchoMode(QLineEdit::Password);
	ui.lineEdit_input_password_3->setEchoMode(QLineEdit::Password);
	Alldrow();
	
}

void  MainWindow::Alldrow() {
	drowUsers(ui.tableWidget_admin_panel);
	drowReaders(ui.tableWidget_readers);
	drow(ui.tableWidget);
	drow(ui.tableWidget_reader_book);
	drowRentBooksTableLibr(ui.tableWidget_reader_book_3);
	drowrentBookUser(ui.tableWidget_reader_book_2);
}

void MainWindow::on_pushButton_add_book_clicked() {
	if (ui.label_3->text() == "User offline") {
		if (!showCheckBox_librarian("You are not logged in to your account"))
			return;
	}

	Book new_add_book(ui.lineEdit_input_title_book->text().toStdString(),
		ui.lineEdit_input_autho_book->text().toStdString(),
		ui.lineEdit_input_genre_book->text().toStdString(),
		ui.lineEdit_input_year_book->text().toInt(),
		ui.lineEdit_input_page_book->text().toInt(),
		ui.lineEdit_input_count_book->text().toInt());

	library.addBookToFile("databasy_books.txt", new_add_book);

	ui.lineEdit_input_title_book->clear();
	ui.lineEdit_input_autho_book->clear();
	ui.lineEdit_input_genre_book->clear();
	ui.lineEdit_input_year_book->clear();
	ui.lineEdit_input_count_book->clear();
	ui.lineEdit_input_page_book->clear();
	Alldrow();
}

void MainWindow::on_pushButton_deleted_book_clicked() {
	if (ui.label_3->text() == "User offline") {
		if (!showCheckBox_librarian("You are not logged in to your account"))
			return;
	}

	// Получаем номер выбранной строки
	int row_lib = ui.tableWidget->currentRow();

	// Проверяем, что строка действительно выбрана
	if (row_lib != -1)
		ui.tableWidget->removeRow(row_lib);

	library.delet_object_file_and_table("databasy_books.txt", row_lib);
	Alldrow();
	ui.tableWidget->setCurrentCell(-1, -1);
}

// Вход рег библиотекаря
void MainWindow::on_pushButton_input_acc_clicked() {

	std::string login = ui.lineEdit_input_login->text().toStdString();
	std::string password = ui.lineEdit_input_password->text().toStdString();

	for (int i = 0; i < library.getSizeUsers(); i++) {
		Users data = library.getVecUsers()[i];
		if (data.checkUsers(login, password, "librarian")) {
			ui.label_3->setStyleSheet("QLabel { color : green; background-color: #333333; }");
			ui.label_3->setText(login.c_str());
			ui.lineEdit_input_login->clear();
			ui.lineEdit_input_password->clear();
			return;
		}
	}

	showCheckBox_librarian("An incorrect password has been entered or there is no such user");
	Alldrow();
}

void MainWindow::on_pushButton_reg_acc_clicked() {
	std::string name = ui.lineEdit_input_reg_log_name->text().toStdString();
	std::string login = ui.lineEdit_input_reg_log->text().toStdString();
	std::string password = ui.lineEdit_input_reg_pass->text().toStdString();
	std::string password2 = ui.lineEdit_input_reg_pass_repit->text().toStdString();

	if (name.empty() || login.empty() || password.empty() || password2.empty()) {
		if (!showCheckBox_librarian("You have not filled in all the fields"))
			return;
	}

	Users new_user("librarian", login, password, name, "0");
	new_user.writeToFile_Users(new_user);
	Alldrow();
}


// Рег и вход читателя в систему
void MainWindow::on_pushButton_reg_acc_reader_clicked() {
	std::string name = ui.lineEdit_input_reg_log_name_3->text().toStdString();
	std::string login = ui.lineEdit_input_reg_log_3->text().toStdString();
	std::string password = ui.lineEdit_input_reg_pass_3->text().toStdString();
	std::string password2 = ui.lineEdit_input_reg_pass_repit_3->text().toStdString();

	if (name.empty() || login.empty() || password.empty() || password2.empty()) {
		if (!showCheckBox_reader("You have not filled in all the fields"))
			return;
	}

	Users new_user("reader", login, password, name, "0");
	new_user.writeToFile_Users(new_user);
	Alldrow();
}


void  MainWindow::on_pushButton_input_acc_reader_clicked() {

	std::string log_user = ui.lineEdit_input_login_3->text().toStdString();
	std::string pass_user = ui.lineEdit_input_password_3->text().toStdString();

	for (int i = 0; i < library.getSizeUsers(); i++) {
		Users data = library.getVecUsers()[i];
		if (data.checkUsers(log_user, pass_user, "reader")) {
			ui.label_5->setStyleSheet("QLabel { color : green; background-color: #333333; }");
			std::string onl = "Online: " + log_user;
			ui.label_5->setText(onl.c_str());
			ui.lineEdit_input_login_3->clear();
			ui.lineEdit_input_password_3->clear();
			Alldrow();
			return;
		}
	}

	showCheckBox_reader("You have not filled in all the fields");
	Alldrow();
}

void MainWindow::on_pushButton_rent_book_clicked() {

	// Получаем номер выбранной строки
	if (!showCheckBox_reader("To rent a book, you need to log in to your account"))
		return;

	int row_lib = ui.tableWidget_reader_book->currentRow();
	int count_rent_books = ui.lineEdit_input_count_rent_book->text().toInt();

	Book bookrent = library.getVecBook()[row_lib];

	//Проверяем, что строка действительно выбрана
	if (row_lib != -1) {
		Book data = library.getVecBook()[row_lib];
		if (data.getCount() >= count_rent_books) {
			data.setCount(count_rent_books * -1);

			library.addBookToFile("databasy_books.txt", data);
			Alldrow();
		}
	}

	std::ofstream file("databasy_rent_books.txt", std::ios_base::app);
	std::string login = ui.label_5->text().toStdString();
	std::string data = ui.dateEdit->text().toStdString();
	std::string name = login.substr(login.find(": ") + 2);  // +2, чтобы пропустить ": "

	file << name << "\t" << data << "\t" << bookrent.getTitle() << "\t" << bookrent.getAuthor() << "\t" << bookrent.getGenre() << "\t"
		<< bookrent.getYear() << "\t" << bookrent.getPages() << "\t" << count_rent_books << "\n";
	
	Alldrow();
	file.close();
	drowrentBookUser(ui.tableWidget_reader_book_2);
}

void MainWindow::on_pushButton_return_book_clicked() {

	// Получаем номер выбранной строки
	if (!showCheckBox_reader("To return a book, you need to log in to your account"))
		return;

	std::vector<std::vector<std::string>> data = library.rent_books.readFileRentBooks();

	int row = ui.tableWidget_reader_book_2->currentRow();
	
	// Считываем всю строку
	int column_count = ui.tableWidget_reader_book_2->columnCount();
	int count_book = ui.lineEdit_return_book->text().toInt();
	
	std::vector<std::string> row_data;
	for (int i = 0; i < column_count; ++i) {
		QTableWidgetItem const* item = ui.tableWidget_reader_book_2->item(row, i);
		if (item) {
			row_data.push_back(item->text().toStdString());
		}
		else {
			row_data.push_back("");
		}
	}
	
	if (count_book <= stoi(row_data[6])) {

		for (int i = 0; i < data.size(); i++) {
			if (data[i][3] == row_data[2] && data[i][4] == row_data[3] && data[i][7] == row_data[6]) {
				if (stoi(data[i][7]) - count_book == 0) {
					data.erase(data.begin() + i);
					break;
				}
				else {
					data[i][7] = std::to_string(stoi(data[i][7]) - count_book);
				}
			}
		}

		std::ofstream outfile("databasy_rent_books.txt");
		outfile << "Reader" << "\t" << "Data" << "\t" << "rent" << "\t" << "Title" << "\t" << "Author" << "\t" << "Genre" << "\t" << "Year" << "\t" << "Pages" << "\t" << "Count" << "\n";
		for (const auto& row : data) {
			for (const auto& col : row) {
				outfile << col << "\t";
			}
			outfile << "\n";
		}
		outfile.close();

		Book book = BookFactory::createBook(row_data[1], row_data[2], row_data[3], stoi(row_data[4]), stoi(row_data[5]), count_book);
		library.addBookToFile("databasy_books.txt", book);
		Alldrow();
		drowrentBookUser(ui.tableWidget_reader_book_2);
		return;
	}
	
	if (!showCheckBox_reader("You don't have that many books to return"))
		return;
	Alldrow();
	drowrentBookUser(ui.tableWidget_reader_book_2);
	
}

void MainWindow::on_pushButton_filter_book_clicked() {
	QString title_data  = ui.lineEdit_filter_title->text();
	QString author_data = ui.lineEdit_filter_autho->text();
	QString genre_data  = ui.lineEdit_filter_genre->text();
	QString year_data   = ui.lineEdit_filter_year->text();
	QString pages_data  = ui.lineEdit_filter_page->text();


	filterAndDraw(ui.tableWidget, genre_data, title_data, author_data, year_data, pages_data);
}

void MainWindow::on_pushButton_reset_filter_clicked() {
	drow(ui.tableWidget);
}

void MainWindow::on_pushButton_filter_book_redear_clicked() {
	QString title_data  = ui.lineEdit_filter_title_4->text();
	QString author_data = ui.lineEdit_filter_autho_4->text();
	QString genre_data  = ui.lineEdit_filter_genre_4->text();
	QString year_data   = ui.lineEdit_filter_year_4->text();
	QString pages_data  = ui.lineEdit_filter_page_4->text();

	filterAndDraw(ui.tableWidget_reader_book, genre_data, title_data, author_data, year_data, pages_data);
}

void MainWindow::on_pushButton_reset_filter_reader_clicked() {
	drow(ui.tableWidget_reader_book);
}

bool MainWindow::showCheckBox_reader(std::string messang) {
	if (ui.label_5->text() == "User offline") {
		QMessageBox msgBox;
		msgBox.setIconPixmap(QPixmap("d:/Desktop/.A_Porgramm/Course_OOP_QT/labriory_curs/icon.png")); // Установить картинку
		msgBox.setStyleSheet("QMessageBox { color: #FFFFFF; background-color: rgb(51, 51, 51);font-weight: bold; font-family: Trebuchet MS; font-size: 10pt;}"
			"QMessageBox QLabel {color: #FFFFFF;font-weight: bold; font-family: Trebuchet MS; font-size: 10pt;}"
			"QMessageBox QPushButton {background-color: #4B4E5A;; color: #FFFFFF;font-weight: bold; font-family: Trebuchet MS; font-size: 10pt;}");

		msgBox.setText(QString::fromStdString(messang));
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle("Error");
		msgBox.exec();

		return false;
	}

	return true;
}

bool MainWindow::showCheckBox_librarian(std::string messang) {
	if (ui.label_3->text() == "User offline") {
		
		QMessageBox msgBox;

		msgBox.setIconPixmap(QPixmap("d:/Desktop/.A_Porgramm/Course_OOP_QT/labriory_curs/icon.png")); // Установить картинку
		msgBox.setStyleSheet("QMessageBox { color: #FFFFFF; background-color: rgb(51, 51, 51);font-weight: bold; font-family: Trebuchet MS; font-size: 10pt;}"
			"QMessageBox QLabel {color: #FFFFFF;font-weight: bold; font-family: Trebuchet MS; font-size: 10pt;}"
			"QMessageBox QPushButton {background-color: #4B4E5A;; color: #FFFFFF;font-weight: bold; font-family: Trebuchet MS; font-size: 10pt;}");

		msgBox.setText(QString::fromStdString(messang));
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle("Error");
		msgBox.exec();

		return false;
	}

	return true;
	
}

void MainWindow::drowReaders(QTableWidget* table) {
	// Устанавливаем количество строк и столбцов в таблице

	table->setRowCount(library.getSize_Readers());
	table->setColumnCount(3);

	// Добавляем книги в таблицу
	for (int i = 0; i < library.getSize_Readers(); i++) {

		table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(library.getVecReaders()[i].getLogin())));
		table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(library.getVecReaders()[i].getName())));
		table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(library.getVecReaders()[i].getName())));
	}

	// Устанавливаем размер колонок по содержимому
	table->resizeColumnsToContents();
}

void MainWindow::drow(QTableWidget* table) {
	// Устанавливаем количество строк и столбцов в таблице

	table->setRowCount(library.getSize());
	table->setColumnCount(6);

	// Добавляем книги в таблицу
	for (int i = 0; i < library.getSize(); i++) {
		Book book = library.getVecBook()[i];
		table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(book.getTitle())));
		table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(book.getAuthor())));
		table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(book.getGenre())));
		table->setItem(i, 3, new QTableWidgetItem(QString::number(book.getYear())));
		table->setItem(i, 4, new QTableWidgetItem(QString::number(book.getPages())));
		table->setItem(i, 5, new QTableWidgetItem(QString::number(book.getCount())));
	}

	// Устанавливаем размер колонок по содержимому
	table->resizeColumnsToContents();
}

void MainWindow::drowUsers(QTableWidget* table) {
	// Устанавливаем количество строк и столбцов в таблице

	table->setRowCount(library.getSizeUsers());
	table->setColumnCount(4);

	table->setHorizontalHeaderLabels(QString("Status;Login;Password;Name").split(";"));

	// Добавляем user'ов в таблицу
	for (int i = 0; i < library.getSizeUsers(); i++) {
		Users user = library.getVecUsers()[i];
		table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(user.getStatus())));
		table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(user.getLogin())));
		table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(user.getPassword())));
		table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(user.getName())));
	}
	// Устанавливаем размер колонок по содержимому
	table->resizeColumnsToContents();
}

void MainWindow::drowrentBookUser(QTableWidget* table) {

	std::vector<std::vector<std::string>> tokens = library.rent_books.readFileRentBooks();

	Users user(ui.label_5->text().toStdString().substr(8));

	table->setRowCount(tokens.size());

	int q = 0;
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i][0] == ui.label_5->text().toStdString().substr(8)) {
			for (int j = 1; j < tokens[i].size(); j++) {
				if (tokens[i][0] == ui.label_5->text().toStdString().substr(8)) {
					table->setItem(q, j - 1, new QTableWidgetItem(QString::fromStdString(tokens[i][j])));
				}
			}
			q += 1;
		}
	}
}

void  MainWindow::drowRentBooksTableLibr(QTableWidget* table) {

	int rowcount = 0;

	for (int i = 0; i < library.rent.size(); i++)
		for (int j = 0; j < library.rent[i].rent_books.size(); j++)
			rowcount++;

	table->setColumnCount(7);
	table->setRowCount(rowcount);
	table->setHorizontalHeaderLabels(QString("Login;Data rent;Title;Author;Genre;Year;Pages").split(";"));
	table->setItem(1, 0, new QTableWidgetItem(QString::fromStdString("ddwqdqw")));

	for (int i = 0; i < library.rent.size(); i++) {
		for (int j = 0; j < library.rent[i].rent_books.size(); j++) {
			table->setItem(j, 0, new QTableWidgetItem(QString::fromStdString(library.rent[i].user.getLogin())));
			table->setItem(j, 1, new QTableWidgetItem(QString::fromStdString(library.rent[i].rent_books[j].getDataRent())));
			table->setItem(j, 2, new QTableWidgetItem(QString::fromStdString(library.rent[i].rent_books[j].getTitle())));
			table->setItem(j, 3, new QTableWidgetItem(QString::fromStdString(library.rent[i].rent_books[j].getAuthor())));
			table->setItem(j, 4, new QTableWidgetItem(QString::fromStdString(library.rent[i].rent_books[j].getGenre())));
			table->setItem(j, 5, new QTableWidgetItem(QString::number(library.rent[i].rent_books[j].getYear())));
			table->setItem(j, 6, new QTableWidgetItem(QString::number(library.rent[i].rent_books[j].getPages())));
		}

	}

}

void MainWindow::filterAndDraw(QTableWidget* table, QString genre, QString title, QString author, QString year, QString pages) {
	// Очищаем таблицу
	table->clearContents();
	table->setRowCount(0);

	// Создаем список книг, которые будем отображать
	std::vector<Book> filteredBooks;

	// Делаем проверку на введенные параметры и фильтруем книги в соответствии с ними
	if (!genre.isEmpty()) {
		for (Book& book : library.getVecBook()) {
			if (book.getGenre() == genre.toStdString()) {
				filteredBooks.push_back(book);
			}
		}
	}
	else {
		filteredBooks = library.getVecBook();
	}

	if (!title.isEmpty()) {
		filteredBooks.erase(remove_if(filteredBooks.begin(), filteredBooks.end(),
			[&title](Book& book) { return book.getTitle() != title.toStdString(); }),
			filteredBooks.end());
	}

	if (!author.isEmpty()) {
		filteredBooks.erase(remove_if(filteredBooks.begin(), filteredBooks.end(),
			[&author](Book& book) { return book.getAuthor() != author.toStdString(); }),
			filteredBooks.end());
	}

	if (!year.isEmpty()) {
		filteredBooks.erase(remove_if(filteredBooks.begin(), filteredBooks.end(),
			[&year](Book& book) { return book.getYear() != year.toInt(); }),
			filteredBooks.end());
	}

	if (!pages.isEmpty()) {
		filteredBooks.erase(remove_if(filteredBooks.begin(), filteredBooks.end(),
			[&pages](Book& book) { return book.getPages() != pages.toInt(); }),
			filteredBooks.end());
	}

	// Устанавливаем количество строк и столбцов в таблице
	table->setRowCount(filteredBooks.size());
	table->setColumnCount(6);

	// Добавляем книги в таблицу
	for (int i = 0; i < filteredBooks.size(); i++) {
		Book book = filteredBooks[i];
		table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(book.getTitle())));
		table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(book.getAuthor())));
		table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(book.getGenre())));
		table->setItem(i, 3, new QTableWidgetItem(QString::number(book.getYear())));
		table->setItem(i, 4, new QTableWidgetItem(QString::number(book.getPages())));
		table->setItem(i, 5, new QTableWidgetItem(QString::number(book.getCount())));
	}

	// Устанавливаем размер колонок по содержимому
	table->resizeColumnsToContents();

	if (filteredBooks.empty() == true) {
		QMessageBox msgBox;
		msgBox.setIconPixmap(QPixmap("d:/Desktop/.A_Porgramm/Course_OOP_QT/labriory_curs/icon.png")); // Установить картинку
		msgBox.setStyleSheet("QMessageBox { color: #FFFFFF; background-color: rgb(51, 51, 51);font-weight: bold; font-family: Trebuchet MS; font-size: 10pt;}"
			"QMessageBox QLabel {color: #FFFFFF;font-weight: bold; font-family: Trebuchet MS; font-size: 10pt;}"
			"QMessageBox QPushButton {background-color: #4B4E5A;; color: #FFFFFF;font-weight: bold; font-family: Trebuchet MS; font-size: 10pt;}");

		msgBox.setText(QString::fromStdString("There is no such book"));
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle("Error");
		msgBox.exec();
	}

}


MainWindow::~MainWindow() {}
