#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::experimental::filesystem;

bool GetFileToArray(std::string FileName, std::vector<std::string>& VectorOfSting) {

	// ��������� ����
	ifstream in(FileName.c_str());

	int size_vector = 0;

	if (!in) {
		cerr << "�� ������� ������� ���� : " << FileName << endl;
		return false;
	}

	// ��������� ��������� ������ �� ����� �� �����.
	string str;
	while (getline(in, str)) {
		// ���� ������ ������ ������ 0 �� ����� � ������ VectorOfSting
		if (str.size() > 0) {
			size_vector++;
			VectorOfSting.push_back(str);
		}
		else {
			cerr << "���� ����" << endl;
		}
	}

	in.close();
	return true;
}

string LZ77(string input, int option, string path, string dir_res);

int main()
{
	setlocale(LC_ALL, "Russian");


	string input, result, method_text;
	int method, option2;

	long long int option;

	string intro = R"(
-------------------------------------------------------------------------------
Hi, � �������� ���������  ^_^ , ���� ����� ������������ ���� ����� .txt.
)";


main_menu:
	cout << intro;
	std::string path = fs::current_path().string();

	string main_menu = R"(
-------------------------------------------------------------------------------
 ����� ����������! ��������� ������� ������ ������� txt � ���������� )" + path + R"(\\compression:
   1- LZ-77
   0- ����� �� ���������
 ����������� ���������� ����� ����������.
  > )";

	path += "\\compression\\test.txt";

	cout << main_menu;
	cin >> method;

	if (method == 1)
		method_text = "LZ-77";
	else if (method == 0) {
		return 0;
	}
	else
	{
		system("cls");
		goto main_menu;
	}

method_menu:
	system("cls");

	string main_menu_2 = R"(
-------------------------------------------------------------------------------
 �������� ��� ���������� ��������� )" + method_text + R"(
   1-   ������������
   2-   ������������
   0- <-�����
 ����������� ���������� ����� ����������.
  > )";

	cout << main_menu_2;
	cin >> option;

	if (option == 1)
	{
		system("cls");

		string lz77_Compression = R"(
-------------------------------------------------------------------------------
 )" + method_text + R"( >  ������������� : �������� ���� ��� ���������. 
)";
		cout << lz77_Compression << endl;

		int shet = 0;
		std::vector<std::string> Dir;

		for (auto& entry : fs::directory_iterator("compression"))
		{
			Dir.push_back(fs::absolute(entry).string());
			cout << ++shet << " " << entry.path() << endl;
		}

		cout << "\n ������� ����� ������������ �����. \n ";

	method_file:
		cin >> option;

		if (option > shet || option == 0) {
			cout << "\n ��� ���������� �����. \n ";
			goto method_file;
		}

		system("cls");

		string dir_res = Dir[option - 1];

		if (method == 1)
			result = LZ77(input, 1, path, dir_res);
		else
		{
			system("cls");
			goto main_menu;
		}

		cout << "\n �����! : " << result << endl;

	back_1:
		cout << "\n ������� 0, ����� ������� � ����. ��� 1 ����� ���������. \n ";
		cin >> option2;

		if (option2 == 0)
		{
			system("cls");
			goto main_menu;
		}
		else if (option2 == 1)
			goto method_menu;
		else
			goto back_1;
	}
	else if (option == 2)
	{
		system("cls");

		string lz77_Compression = R"(
-------------------------------------------------------------------------------
 LZ-77 >  ������������� :)";
		cout << lz77_Compression << endl;
		cout << "\t ��� ���� �����, ��� �� ������� : ";
		cin.ignore();
		getline(cin, input);
		main_menu;
		//if (method == 1)
		//	result = LZ77(input, 2);
		//else
		//	main_menu;

	back_2:
		cout << "\n ������� 0, ����� ������� � ����. ��� 1 ����� ���������. \n  > ";
		cin >> option2;

		if (option2 == 0)
		{
			system("cls");
			goto main_menu;
		}
		else if (option2 == 1)
			goto method_menu;
		else
			goto back_2;

	}
	else if (option == 0)
	{
		system("cls");
		goto main_menu;
	}
	else
		goto method_menu;


	cin.get();
	cin.ignore();
	return 0;
}

// ���������
string LZ77(string input, int option, string path, string dir_res)
{
	string result;

	if (option == 1)
	{
	check_char:		

		//������ ��� ���������� ����� ������
		std::vector<std::string> VectorOfSting;

		//��������� � �������� ������� 
		bool ret = GetFileToArray(dir_res, VectorOfSting);

		if (ret) {
			string result = "";

			for (std::string& line : VectorOfSting) {
				for (int shet = 0; shet < line.size(); shet++) {
					int start = 0, siz = 0, opt = 0;
					char ch = line[shet];
					for (int shet_2 = 0; shet_2 < shet; shet_2++) {
						if (line[shet_2] == line[shet + opt] && shet + opt <= line.size()) {
							opt++;
						}
						else {
							if (opt > siz) {
								siz = opt;
								start = shet;
								shet_2 = start + 1;
								ch = line[shet + opt];
							}
						}
					}
					result += to_string(start) + "," + to_string(siz) + "," + ch + " ";

					shet += siz;
				}

			}
			cout << result << endl;
		}
		else
		{
			cout << "��� ����� � �����, ����� ��������� ������� Enter \n";
			getline(cin, input);		// ������ ������� ������
			goto check_char;
		}

		return result;
	}
	else if (option == 2)
	{

		return result;
	}
	else
	return result;
}
