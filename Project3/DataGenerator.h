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
	map<string, pair<int, int> > limits;
	int numCities;

public:
	/*Constructors*/
	DataGenerator(int numCities);
  DataGenerator(int numCities, int minRoadCap, int maxRoadCap, int minPopulation, int maxPopulation);

	/*Mutators*/
	string GenerateCityName();
	void GenerateCities();

	/*Display*/
	void OutputToCSV(string filename);
	void Debug() { cityGraph->PrintGraph(); }
};
