#include "Library.h"

Library::Library() {}

Library::~Library() {}

void Library::setBooks(Book created_book_data, int index) {
    books[index] = created_book_data;
}

int Library::getSize() {
	return books.size();
}

int Library::getSizeUsers() {
	return users.size();
}

int Library::getSize_Readers() {
	return readers.size();
}

std::vector<Book> Library::getVecBook() {
    return books;
}

std::vector<Users> Library::getVecUsers() {
    return users;
}

std::vector<Reader> Library::getVecReaders() {
    return  readers;
}


// Функция для добавления книг из файла
void Library::addBookToFile(const std::string& fileName, Book book) {
    // Открываем файл для записи в конец
    std::ofstream file(fileName, std::ios_base::app);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
    }

    for (int i = 0; i < books.size(); i++) {
        if (books[i].getTitle() == book.getTitle()) {
            int count = books[i].getCount() + book.getCount();
            books[i].setCount(count);
            writeBooksToFile(fileName, books);
            return;
        }
    }

    books.push_back(book);

    writeBooksToFile(fileName, books);
    // Закрываем файл
    file.close();
}

void Library::delet_object_file_and_table(const std::string& fileName, int i) {
    books.erase(books.begin() + i);
    writeBooksToFile(fileName, books);

}

// Функция для чтения книг из файла
void Library::readBooksFromFile(const std::string& filename) {
    std::ifstream input(filename);
    if (!input.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Skip the first line (column headers)
    std::string line;
    std::getline(input, line);

    // Read the remaining lines and create Book objects
    while (std::getline(input, line)) {
        std::istringstream ss(line);
        std::string title, author, genre, yearStr, pagesStr, count_str;
        std::getline(ss, title, '\t');
        std::getline(ss, author, '\t');
        std::getline(ss, genre, '\t');
        std::getline(ss, yearStr, '\t');
        std::getline(ss, pagesStr, '\t');
        std::getline(ss, count_str, '\t');

        try {
            int year = std::stoi(yearStr);
            int pages = std::stoi(pagesStr);
            int count = std::stoi(count_str);

            Book book = BookFactory::createBook(title, author, genre, year, pages, count);
            books.push_back(book);
        }
        catch (const std::exception& ex) {
            std::cerr << "Failed to read book data: " << ex.what() << std::endl;
        }
    }
}

// Функция для пользователей из файла
void Library::readUsersFromFile(const std::string& filename ) {
    // Открываем файл для чтения
    std::ifstream file(filename);

    // Проверяем, удалось ли открыть файл
    if (!file.is_open()) {
        std::cerr << "Ошибка: Невозможно открыть файл для чтения.\n";
        return;
    }

    // Пропускаем заголовок
    std::string line;
    std::getline(file, line);

    // Считываем данные и добавляем их в вектор Users
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> tokens(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
        if (tokens.size() != 5) {
            std::cerr << "Ошибка: Неверный формат данных в файле.\n";
            return;
        }
        users.emplace_back(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
    }

    // Закрываем файл
    file.close();
}

// Функция поиска из файла reader и заполнения их в вектор
// Заполняем структуру readers из данных файла
void Library::readReaderFromFile() {
	// Открываем файл для чтения
	std::ifstream file("databasy_users.txt");

	// Проверяем, удалось ли открыть файл
	if (!file.is_open()) {
		std::cerr << "Ошибка: Невозможно открыть файл для чтения.\n";
		return;
	}

	// Пропускаем заголовок
	std::string line;
	std::getline(file, line);

	// Считываем данные и добавляем их в вектор Users
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::vector<std::string> tokens(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
		std::string status = tokens[0];
		std::string login = tokens[1];
		std::string name = tokens[3];
		if (status == "reader") {
			readers.push_back(Reader(login, name));
		}
	}

	// Закрываем файл
	file.close();
}

void Library::distribution_readers() {
    std::vector<std::vector<std::string>> data = rent_books.readFileRentBooks();
    Users user1(data[0][0]);

    RentBooksBuilder rbb = RentBooksBuilder();
    rbb.setUser(user1);
    for (int i = 0; i < data.size(); i++) {
        if (user1.getLogin() != data[i][0]) {
            rent.push_back(rbb.setUser(user1).build());
            rbb.clear();
            user1.setLogin(data[i][0]);
            std::cout << user1.getLogin();
        }
        Book book1(data[i][1], data[i][2], data[i][3], data[i][4], std::stoi(data[i][5]), std::stoi(data[i][6]), std::stoi(data[i][7]));
        rbb.addBook(book1);
    }
    rent.push_back(rbb.setUser(user1).build());
}

