#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include "Message.h"
#include "Controller.h"

int main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");
	
	WelcomeMenu();
}

int WelcomeMenu() {
	system("cls");
	message.StrMessage("intro");
	message.StrMessage("main_menu");

	int main;
	std::cin >> main;

	if (main == 1) {
		mainMenu_2();
	}
	else if (main == 0) {
		exit(0);
	}
	else
	{
		WelcomeMenu();
	}
}

void mainMenu_2() {
	system("cls");
	message.StrMessage("main_menu_2");

	int main;
	std::cin >> main;

	if (main == 1) {
		system("cls");
		lz77_Compression();
	}
	else if (main == 2) {
		lz77_Decoder();
	}
	else if (main == 0) {
		WelcomeMenu();
	}
	else
	{
		mainMenu_2();
	}

}
void lz77_Compression() {
	message.StrMessage("lz77_Compression");

	int main;
	std::cin >> main;

	if (main == 1) {
		system("cls");
		lz77_Compression_1();
	}
	else if (main == 2) {
		lz77_Compression_2();
	}
	else if (main == 0) {
		mainMenu_2();
	}
	else
	{
		lz77_Compression();
	}

}

void lz77_Compression_1() {
	message.StrMessage("lz77_Compression_1");

	std::vector<std::string> Dir;
	int shet = 0, option;

	for (auto& entry : fs::directory_iterator("compression"))
	{
		Dir.emplace_back(fs::absolute(entry).string());
		std::cout << ++shet << " " << entry.path() << std::endl;
	}

	std::cout << "\n Введите номер запускаемого файла. \n ";

	std::cin >> option;

	if (option == 0) {
		mainMenu_2();
	}

	if (option > shet || option == 0) {
		system("cls");
		std::cout << "\n Нет выбранного файла. \n ";
		lz77_Compression_1();
	}

	std::string dir_res = Dir[option - 1];

	if (option > 0) {
		LZ77(dir_res);
	}
	else
	{
		lz77_Compression_1();
	}
}

void lz77_Compression_2() {
	message.StrMessage("lz77_Compression_2");

	std::string Dir;

	std::cin >> Dir;

	if (Dir == "0") {
		mainMenu_2();
	}

	std::ifstream iff(Dir);
	if (iff.bad() == true) {
		std::cout << "\n Нет выбранного файла. \n ";
		lz77_Compression_2();
	}
	else {
		LZ77(Dir);
	}
}

void lz77_Decoder() {
	system("cls");
	message.StrMessage("lz77_Decoder");

	int main;
	std::cin >> main;

	if (main == 0) {
		mainMenu_2();
	}
	else
	{
		lz77_Decoder();
	}
}

// архиватор
void LZ77(std::string dir_res)
{
	std::string result;

	int buffer = bufferSize();

	//массив для сохранения путей файлов
	std::vector<std::string> VectorOfSting;

	//обращение к файловой системе 
	bool ret = GetFileToArray(dir_res, VectorOfSting);

	if (ret) {
		std::string result = "";
		int shet_2 = 0;

		for (std::string& line : VectorOfSting) {

			for (int shet = 0; shet <= line.size(); shet++) {
				if (line[0] == '\r' || (shet > 0 && line[shet - 1] == '\r')) {
					continue;
				}
				int start = 0, siz = 0, opt = 0, cool_start = 0;
				std::string ch = " ";

				if (line[shet] == '\r') {
					ch = ' ';
				}
				else
					ch = line[shet];

				if (ch == "") {
					continue;
				}

				if (shet >= buffer) {
					shet_2 = shet - buffer;
				}
				else {
					shet_2 = 0;
				}

				start = shet_2;

				for (shet_2; shet_2 < shet; shet_2++) {

					if (opt == 0) {
						cool_start = shet_2;
					}

					if (line[shet_2] == line[shet + opt]) {
						opt++;
					}

					if (line[cool_start] == line[shet + opt] && shet_2 + 1 == shet) {

						if (shet > buffer) {
							shet_2 = cool_start - 1;
						}
						else {
							shet_2 = -1;
						}
					}

					if (shet_2 >= 0)
						if (line[shet_2 + 1] != line[shet + opt]) {
							if (siz <= opt && opt != 0) {
								siz = opt;
								ch = line[shet + opt];
								if (line[shet + opt] == '\r') {
									ch = ' ';
								}

								start = shet - cool_start;

								shet_2 = cool_start;

								opt = 0;
							}
						}
				}
				if (siz == 0)
					start = 0;

				std::cout << start << "," << siz << "," << ch << " ";
				shet += siz;
			}

		}
		lz77_Compression();
	}
	else
	{
		int intro;
		std::cout << "Нет файла в папке, чтобы повторить нажмите Enter \n";
		std::cin >> intro;
		lz77_Compression_1();
	}
}

bool GetFileToArray(std::string FileName, std::vector<std::string> & VectorOfSting) {

	// Открываем файл
	std::ifstream in(FileName, std::ios::in | std::ios::binary);

	int size_vector = 0;

	if (!in) {
		std::cerr << "Не удается открыть файл : " << FileName << std::endl;
		return false;
	}

	// Считываем следующую строку из файла до конца.
	std::string str;
	while (std::getline(in, str)) {
		// если размер строки больше 0 то пушим в массив VectorOfSting
		if (str.size() > 0) {
			size_vector++;
			VectorOfSting.emplace_back(str);
		}
	}

	in.close();
	return true;
}

int bufferSize() {
	std::cout << "Укажите размер буфера \n";
	int buffer;
	std::cin >> buffer;

	if (buffer <= 0) {
		buffer = bufferConst;
	}
	return buffer;
}