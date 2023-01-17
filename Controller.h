#pragma once
Message message;

namespace fs = std::experimental::filesystem;
int const bufferConst = 10000000;

int WelcomeMenu();
void mainMenu_2();
void lz77_Compression();
void lz77_Compression_1();
void lz77_Compression_2();
void lz77_Decoder();
bool GetFileToArray(std::string FileName, std::vector<std::string>& VectorOfSting);
void LZ77(int option, int path, std::string dir_res);
int bufferSize();