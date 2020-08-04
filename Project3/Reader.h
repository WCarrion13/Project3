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
	Graph* GetGraph() { return graph; }		//Return the graph describing the connections between cities
	map<string, City*>* GetCityList() { return cityList; }	//Return a list of every city and its object
	string GetRandomCity();	//Find random city in graph
	string GetRandomCity(string exclude);	//Find random city in graph, excluding input
	string GetRandomCity(vector<string> exclude);	//Find random city in graph, excluding input

	//Mutators	
	void AddAdjCities();		//Add adj city map to each city for easy access

	//Utility
	void ReadCSV(string filename);	//Read all data from CSV file into data structures

};

