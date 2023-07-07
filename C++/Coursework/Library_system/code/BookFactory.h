#pragma once
#include "Book.h"

class BookFactory{
public:
    static Book createBook(const std::string& title, const std::string& author, const std::string& genre, int year, int pages, int count) {
        return Book(title, author, genre, year, pages, count);
    }
};

