#include "Users.h"

Users::Users(std::string const& stat, std::string const& log, std::string const& passw, std::string const& na, std::string const& num) {
    status = stat;
    login = log;
    password = passw;
    name = na;
    number = num;
}


void Users::setLogin(std::string log) {
    login = log;
}

void Users::setPassword(std::string passw) {
    password = passw;
}

void Users::setName(std::string na) {
    name = na;
}

std::string Users::getStatus() {
    return status;
}

std::string Users::getLogin() {
    return login;
}

std::string Users::getPassword() {
    return password;
}

std::string Users::getName() {
    return name;
}

std::string Users::getNumber() {
    return number;
}

bool Users::checkUsers(std::string log, std::string pass, std::string stats) {
    if (login == log && password == pass && status == stats) {
        return true;
    }
    else {
        return false;
    }
}

// Функция для записи вектора книг в файл
void Users::writeToFile_Users(Users user) {
    // Открываем файл для добавления
    std::ofstream file("databasy_users.txt", std::ios::app);

    // Проверяем, удалось ли открыть файл
    if (!file.is_open()) {
        std::cerr << "Ошибка: Невозможно открыть файл для записи.\n";
        return;
    }

    // Записываем пользователя в файл
    file << user.getStatus() << "\t"
        << user.getLogin() << "\t"
        << user.getPassword() << "\t"
        << user.getName() << "\t"
        << user.getNumber() << "\n";
    // Закрываем файл
    file.close();
}
