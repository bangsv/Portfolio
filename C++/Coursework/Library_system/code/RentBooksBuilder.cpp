#include "RentBooksBuilder.h"

RentBooksBuilder& RentBooksBuilder::setUser(const Users& user) {
    rent_books_.user = user;
    return *this;
}

RentBooksBuilder& RentBooksBuilder::addBook(const Book& book) {
    rent_books_.rent_books.push_back(book);
    return *this;
}

RentBooks RentBooksBuilder::build() {
    return rent_books_;
}

void RentBooksBuilder::clear() {
    rent_books_.rent_books.clear();
}

int RentBooksBuilder::size() {
    return rent_books_.rent_books.size();
}