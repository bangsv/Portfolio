#pragma once

#include "Reader.h"
#include "BookFactory.h"
#include "RentBooks.h"
#include "RentBooksBuilder.h"

class Library : public Book{
public:

    Library();
    ~Library();

    int getSize();
    int getSizeUsers();
	int getSize_Readers();
    
    void setBooks(Book created_book_data, int index);
    

    std::string getLogin();

    // ������ � �������� ��������� � ������� � �������
    std::vector<Book> getVecBook();
    std::vector<Users> getVecUsers();
    std::vector<Reader> getVecReaders();
    
    // ������� ��� ���������� ���� �� �����
    void addBookToFile(const std::string& fileName, Book book);
    void addUserToFile(Users user);

    void delet_object_file_and_table(const std::string& fileName, int i);

    // ������� ��� ������ ���� �� �����
    void readBooksFromFile(const std::string& filename);
    void readUsersFromFile(const std::string& filename);

    void readReaderFromFile();

    void distribution_readers();

    RentBooks rent_books;
    std::vector< RentBooks> rent;
    
protected:
    std::vector<Reader> readers;
	std::vector<Users> users; 

private:
    std::vector<Book> books;
};