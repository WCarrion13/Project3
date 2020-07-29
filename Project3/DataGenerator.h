#pragma once
#include <map>
#include <string>
#include <set>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;


class DataGenerator {
	set<string>* cityList;
	char numbers[11] = "0123456789";
	char lettersLC[27] = "abcdefghijklmnopqrstuvwxyz";
	char lettersUC[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string ends[10] = { "ville", "town", "land", "ington", "ford", "ayton", "ester", "ton", "son", "urn"};
	int numCities;
	int minCityNameLength;
	int maxCityNameLength;


public:
	//Constructor
	DataGenerator(int numCities, int minCityNameLength, int maxCityNameLength);

	void GenerateCityNames();
	void GenerateCityAttributes();

	//Returns a randomly-selected alphanumeric character
	char GetRandomChar(string type);

	//Display
	void Debug();
};

