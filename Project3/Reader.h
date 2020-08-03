#pragma once
#include "City.h"
#include "Randomizer.h"
#include <fstream>
#include <sstream>
using namespace rnd;

class Reader {
	Graph* graph;
	map<string, City*>* cityList;

public:
	//Constructor
	Reader() {
		graph = new Graph;
		cityList = new map<string, City*>;
	}
	
	//Accessors
	Graph* GetGraph() { return graph; }
	map<string, City*>* GetCityList() { return cityList; }
	string GetRandomCity();

	//Mutators
	void AddCities();

	//Utility
	void ReadCSV(string filename);

};

