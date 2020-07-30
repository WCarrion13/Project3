#pragma once
#include "City.h"
#include <fstream>
#include <sstream>

class Reader {
private:
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

	//Mutators
	void AddCities();

	//Utility
	void ReadCSV(string filename);

};

