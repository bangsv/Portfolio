#pragma once

#include "Book.h"
#include "Users.h"

class RentBooks{
public:
	
	Users user;
	std::vector<Book> rent_books;
	std::vector<std::vector<std::string>> readFileRentBooks();

};

