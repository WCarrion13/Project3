#pragma once
#include "Graph.h"
#include "Randomizer.h"
#include <fstream>
#include <iomanip>
using namespace rnd;

class DataGenerator {
	Graph* cityGraph;
	vector<string> prefix;
	vector<string> suffix;
	map<string, pair<int, int>> limits;
	int numCities;

public:
	/*Constructor*/
	DataGenerator(int numCities);

	/*Mutators*/
	string GenerateCityName();
	void GenerateCities();

	/*Display*/
	void OutputToCSV(string filename);
	void Debug() { cityGraph->PrintGraph(); }
};