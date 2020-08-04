#pragma once
#include <stdlib.h>
#include <utility>
namespace rnd {
	static const char* numbers = "0123456789";
	static const char* lettersLC = "abcdefghijklmnopqrstuvwxyz";
	static const char* lettersUC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	static int GetRandInt(int min, int max) { return rand() % (max - min + 1) + min; }
	static int GetRandInt(std::pair<int, int> p) { return rand() % (p.second - p.first + 1) + p.first; }
	static char GetNum() { return numbers[GetRandInt(0, 9)]; }
	static char GetLC() { return lettersLC[GetRandInt(0, 25)]; }
	static char GetUC() { return lettersUC[GetRandInt(0, 25)]; }
	static bool GetTF(int chance) { return (GetRandInt(1, chance) == 1) ? true : false; }	//Returns a T/F value based on 1/input
};