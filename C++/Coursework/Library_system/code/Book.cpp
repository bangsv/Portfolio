#include "Book.h"

// ������� ������������� �������� ����� ������
void Book::setAuthor(std::string author) {
    this->author = author;
}
void Book::setTitle(std::string title) {
    this->title = title;
}

void Book::setYear(int year) {
    this->year = year;
}

void Book::setPages(int page) {
    this->pages = page;
}

void Book::setGenre(std::string genre) {
    this->genre = genre;
}

void Book::setCount(int count) {
    this->count = count;
}


std::string Book::getAuthor() {
    return author;
}

std::string Book::getTitle() {
    return title;
}

int Book::getYear() {
    return year;
}

int Book::getPages() {
    return pages;
}

std::string Book::getGenre() {
    return genre;
}

int Book::getCount() {
    return count;
}

std::string Book::getDataRent() {
    return data_rent;
}

// ������� ��� ������ ������� ���� � ����
void Book::writeBooksToFile(const std::string& filename, const std::vector<Book>& books) {
    // ��������� ���� ��� ������
    std::ofstream file(filename);

    // ���������� ���������
    file << "Title\tAuthor\tGenre\tyear\tNumber of pages\tCount\n";

    // ���������� �� ������ ����� ������� � ���������� �� � ����
    for (const auto& book : books) {
        file << book.title << "\t"
            << book.author << "\t"
            << book.genre << "\t"
            << book.year << "\t"
            << book.pages << "\t"
            << book.count << "\n";
    }
    // ��������� ����
    file.close();
}