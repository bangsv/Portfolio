#pragma once

#include "RentBooks.h"

class RentBooksBuilder {
public:
    RentBooksBuilder& setUser(const Users& user);

    RentBooksBuilder& addBook(const Book& book);

    RentBooks build();

    void clear();

    int size();

private:
    RentBooks rent_books_;
};
