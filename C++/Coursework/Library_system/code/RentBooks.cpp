#include "RentBooks.h"


std::vector<std::vector<std::string>> RentBooks::readFileRentBooks() {
	std::ifstream file("databasy_rent_books.txt");

	std::vector<std::vector<std::string>>tokens;
	std::string line;

	int count = 0;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string token;
		std::vector<std::string> row;
		if (count != 0) {
			while (std::getline(iss, token, '\t')) {
				row.push_back(token);
			}
			tokens.push_back(row);
		}
		count++;
	}
	// Сортируем tokens по первому столбцу
	std::sort(tokens.begin() + 1, tokens.end(),
		[](const std::vector<std::string>& row1, const std::vector<std::string>& row2) {
		return row1[0] < row2[0];
	});

	return tokens;
}