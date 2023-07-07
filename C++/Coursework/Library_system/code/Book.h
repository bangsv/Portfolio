#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

class Book {
public:
    Book(std::string title, std::string author, std::string genre, int year, int pages, int count) :
        title(title), author(author), genre(genre), year(year), pages(pages), count(count) { }

    Book(std::string rent, std::string title, std::string author, std::string genre, int year, int pages, int count) :
        data_rent(rent), title(title), author(author), genre(genre), year(year), pages(pages), count(count) { }

    Book() = default;

    // Функция устанавливает значения полей класса
    void setAuthor(std::string author);
    void setTitle(std::string title);

    void setYear(int year);

    void setPages(int page);

    void setGenre(std::string genre);

    void setCount(int count);

  
    std::string getAuthor();

    std::string getTitle();

    int getYear();

    int getPages();

    std::string getGenre();

    int getCount();

    std::string getDataRent();

private:
    std::string title;
    std::string author;
    std::string genre;
    std::string data_rent;
    int year;
    int pages;
    int count;

protected:
    // Функция для записи вектора книг в файл
    void writeBooksToFile(const std::string& filename, const std::vector<Book>& books);
};

