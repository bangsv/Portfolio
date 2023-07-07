#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

#include "HeaderTable.h" 

using namespace std;

Table* table = new Table;

float A = NULL; float B = NULL;

func pointer = &comparison;

void instuction(); // Инстуркция
bool checkSymbol(char c); //Проверка символ ли
string isNumber(string line); //Нахождение вещественого числа в строке

/*
"Команды с одним операндом:\nIN - ввод. (Пример IN a)\nOUT - ввывод. (Пример OUT d)"
"Команды с двумя операндом:\nADD - (+). (Пример ADD a b = a+b)\nSUB - (-). (Пример SUB a b = a-b)"
"MUL - (*). (Пример MUL a b = a*b) DIV - (/). (Пример DIV a b = a/b)"
*/

void IN(void* a); // ✓
void OUT(void* a); //✓
void MOV(void* a, void* b); //Перемещаем данные из символа b в a. ✓
void MUL(void* a, void* b); //MUL - (*) //✓
void ADD(void* a, void* b); //ADD - (+) //✓
void SUB(void* a, void* b); //SUB - (-) // a - b //✓
void DIV(void* a, void* b); // DIV - (/) a / b //✓

template <class Functional> 
void allFunc_DoubleParameter(string& commandString, Functional Func); // Для функций DIV ADD ...
template <class Operation>
void  allFunc_OneParameter(string& commandString, Operation FunC); // Для IN ...

int main() {

	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	instuction();

	InitTable(table, 0, 0);

	ifstream commandTXT;

	try {
		commandTXT.open("command.txt");
	}
	catch (const std::exception& ex) {
		cout << ex.what();
	}

	string commandString((std::istreambuf_iterator<char>(commandTXT)), (std::istreambuf_iterator<char>()));

	cout << endl;

	cout << "Command : "<< endl << commandString << endl;

	string strTime;

	while (!commandString.empty()) {

		if (commandString.find("IN") == 0)
			allFunc_OneParameter(commandString, IN);

		if (commandString.find("OUT") == 0)
			allFunc_OneParameter(commandString, OUT);

		if (commandString.find("ADD") == 0)
			allFunc_DoubleParameter(commandString, ADD);

		if (commandString.find("SUB") == 0)
			allFunc_DoubleParameter(commandString, SUB);

		if (commandString.find("MUL") == 0)
			allFunc_DoubleParameter(commandString, MUL);

		if (commandString.find("DIV") == 0)
			allFunc_DoubleParameter(commandString, DIV);

		if (commandString.find("MOV") == 0)
			allFunc_DoubleParameter(commandString, MOV);

	}
	cout << endl << "Our table finish:" << endl;
	outputTable(table); //Вывод
	cout << endl;

}

void IN(void* a) { // ✓
	float x = rand() / (RAND_MAX + 0.5) + (rand() % 50 + 1) * 1.;
	if (!PutTable((char)a, x, table, pointer))
		cout << "IN: Element " << (char)a << " already in the table" << endl;;
}

void OUT(void* a) { //✓
	float E = NULL;
	ReadTable(table, E, (char)a, pointer);
	if (E == NULL) {
		cerr << "Error OUT hasn't this operand (" << (char)a << ")" << endl;
		return;
	}
	cout << "OUT: " << (char)a << " " << E << endl;
}

void MOV(void* a, void* b) { //Перемещаем данные из символа b в a. ✓
	ReadTable(table, A, (char)b, pointer);
	WriteTable(table, A, (char)a, pointer);
}

void MUL(void* a, void* b) { //MUL - (*) //✓
	if (checkSymbol((char)b)) {
		if (checkSymbol((char)a)) { // Если оба параметра переменные
			ReadTable(table, A, (char)a, pointer);
			ReadTable(table, B, (char)b, pointer);
			WriteTable(table, A * B, (char)b, pointer);
		}
		else if (!checkSymbol((char)a)) { // если есть число пример MUL a * 3.2
			ReadTable(table, B, (char)b, pointer);
			float numberFloat = atof((char*)a);
			WriteTable(table, B * numberFloat, (char)a, pointer);
		}
	}
}

void ADD(void* a, void* b) { //ADD - (+) //✓
	if (checkSymbol((char)b)) {
		if (checkSymbol((char)a)) {
			ReadTable(table, A, (char)a, pointer);
			ReadTable(table, B, (char)b, pointer);
			WriteTable(table, A + B, (char)a, pointer);
		}
		else if (!checkSymbol((char)a)) {
			ReadTable(table, B, (char)b, pointer);
			float numberFloat = atof((char*)a);
			WriteTable(table, B + numberFloat, (char)a, pointer);
		}
	}

}

void SUB(void* a, void* b) { //SUB - (-) // a - b //✓
	if (checkSymbol((char)b)) {
		if (checkSymbol((char)a)) {
			ReadTable(table, A, (char)a, pointer);
			ReadTable(table, B, (char)b, pointer);
			WriteTable(table, B - A, (char)a, pointer);
		}
		else if (!checkSymbol((char)a)) {
			ReadTable(table, B, (char)b, pointer);
			float numberFloat = atof((char*)a);
			WriteTable(table, numberFloat - B, (char)a, pointer);
		}
	}

}

void DIV(void* a, void* b) { // DIV - (/) a / b //✓
	if (checkSymbol((char)b)) {
		if (checkSymbol((char)a)) {
			ReadTable(table, A, (char)a, pointer);
			ReadTable(table, B, (char)b, pointer);
			WriteTable(table, A / B, (char)a, pointer);
		}
		else if (!checkSymbol((char)a)) {
			ReadTable(table, B, (char)b, pointer);
			float numberFloat = atof((char*)a);
			WriteTable(table, numberFloat / B, (char)a, pointer);
		}
	}
}

template <class Functional> 
void allFunc_DoubleParameter(string& commandString, Functional Func) {
	string strTime;
	if (checkSymbol(commandString[commandString.find('\n') - 1])) { //Проверка крайнего с право символа.
		if (checkSymbol(commandString[commandString.find(' ') + 1])) //Проверка крайнего с лево символа.
			Func((void*)commandString[commandString.find(' ') + 1], (void*)commandString[commandString.find('\n') - 1]);
		else if (!checkSymbol(commandString[commandString.find(' ') + 1])) {
			string number_A_str = isNumber(commandString); //Определяем что за число
			const char* char_str_A = number_A_str.c_str();
			Func((void*)commandString[commandString.find('\n') - 1], (void*)char_str_A);
		}
	}

	if (!checkSymbol(commandString[commandString.find('\n') - 1])) {
		
		string number_A_str = isNumber(commandString); //Определяем что за число
		const char* char_str_A = number_A_str.c_str();	
		
		if (checkSymbol(commandString[commandString.find(' ') + 1]))  //Проверка крайнего с лево символа.
			Func( (void*)char_str_A, (void*)commandString[commandString.find(' ') + 1]);
		else if (!checkSymbol(commandString[commandString.find(' ') + 1])) {
			cerr << endl << "ERROR !!!\nProgramm has two numbers,\nbut hasn't variable"<< endl;
			exit(-1);
		}
	}

	strTime.append(commandString, commandString.find('\n') + 1);
	commandString = strTime;
	strTime.clear();

}

template <class Operation>
void  allFunc_OneParameter(string& commandString, Operation FunC) {
	string strTime;
	FunC((void*)commandString[commandString.find('\n') - 1]);
	strTime.append(commandString, commandString.find('\n') + 1);
	commandString = strTime;
	strTime.clear();
}

/* Регулярное выражение для поиска числа в строке
[-]? - Встречается ли символ - в строке 0 или 1 раз
//d - все числа [0-9], + обозначает не взятие одного символа например 4,
а всего числа 421. Символ (.) значит что в числе присутствует точка*/ 
string isNumber(string line) {
	std::smatch m;
	std::regex e("[-]?\\d+.\\d+"); 
	regex_search(line, m, e);
	return m.str();
}

void instuction() {
	cout << "Команды с одним операндом:\nIN - ввод. (Пример IN a)\nOUT - ввывод. (Пример OUT d)" << endl;
	cout << "Команды с двумя операндом:\nADD - (+). (Пример ADD a b = a+b)\nSUB - (-). (Пример SUB a b = a-b)" << endl;
	cout << "MUL - (*). (Пример MUL a b = a*b)\nDIV - (/). (Пример DIV a b = a/b)" << endl;
}

bool checkSymbol(char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}