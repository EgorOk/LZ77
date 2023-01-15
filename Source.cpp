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