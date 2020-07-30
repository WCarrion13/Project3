#pragma once
#include "Graph.h"
#include <fstream>
#include <iomanip>

using namespace std;


class DataGenerator {
private:
	Graph* cityGraph;
	char numbers[11] = "0123456789";
	char lettersLC[27] = "abcdefghijklmnopqrstuvwxyz";
	char lettersUC[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string ends[10] = { "ville", "town", "land", "ington", "ford", "ayton", "ester", "ton", "son", "urn" };
	int numCities;
	int minCityNameLength;
	int maxCityNameLength;
	int minAdjCities = 1;
	int maxAdjCities = 3;
	int minWeight = 1;
	int maxWeight = 10;
	int minPopulation = 10000;
	int maxPopulation = 1000000;
	int minNumShelters = 0;
	int maxNumShelters = 3;
	int minShelterCapacity = 1000;
	int maxShelterCapacity = 10000;
	ofstream file;


public:
	/*Constructor*/
	DataGenerator(int numCities, int minCityNameLength, int maxCityNameLength);

	/*Mutators*/
	string GenerateCityName();
	void GenerateCities();

	/*Utility*/
	int Rand(int min, int max) { return rand() % (max - min + 1) + min; }
	char GetRandomChar(string type);	//Returns a randomly-selected alphanumeric character
	bool Randomizer(int chance) { return (Rand(1, chance) == 1) ? true : false; }	//Returns a T/F value based on 1/input


	/*Display*/
	void OutputToCSV(string filename);
	void Debug();
};