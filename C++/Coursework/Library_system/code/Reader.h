#pragma once

#include "Book.h"
#include "Users.h"

class Reader {
public:

	Reader(std::string name) {
		user.setName(name);
	}

	Reader(std::string nam, std::string log) {
		user.setLogin(log);
		user.setName(nam);
	}

	Reader() = default;
	~Reader() {}

	std::vector<Book> getBooks() {
		return books_rent;
	}

	std::string getName() {
		return user.getName();
	}

	std::string getLogin() {
		return user.getLogin();
	}

private:
	std::vector<Book> books_rent;
	Users user;
	int count_book;
};


