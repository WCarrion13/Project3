#pragma once
#include "Graph.h"

class City {
private:
	string name;
	int population;
	int numShelters;
	int numAdjCities;
	map<string, int> shelters;
	map<string, int>* adjCities;

public:
	//Constructor
	City(string name, int population) {
		this->name = name;
		this->population = population;
	}

	//Mutators
	void AddShelter(string name, int capacity) { shelters[name] = capacity; }
	void AddAdjCity(map<string, int>* adjCities) { this->adjCities = adjCities; }

};

