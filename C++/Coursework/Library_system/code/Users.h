#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

class Users{
public:

    Users(std::string const& stat, std::string const& log, std::string const& passw, std::string const& na, std::string const& num);

    Users(){}
    Users(std::string log) : login(log) {}

    void setLogin(std::string log);

    void setPassword(std::string passw);

    void setName(std::string na);

    std::string getStatus();

    std::string getLogin();

    std::string getPassword();
    std::string getName();

    std::string getNumber();

    bool checkUsers(std::string log, std::string pass, std::string stats);
        
    // Функция для записи вектора книг в файл
    void writeToFile_Users(Users user);

protected:
	std::string password;
	std::string login;
	std::string status;
	std::string name;
	std::string number;
};
 

