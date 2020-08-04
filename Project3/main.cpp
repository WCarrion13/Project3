/*
#pragma once
#include "DataGenerator.h"
#include "Reader.h"

int main() {
	int numCities = 10000;
	DataGenerator gen(numCities);
	Reader reader;
	string filename = "test.csv";

	gen.GenerateCities();		//Generate random data
	gen.OutputToCSV(filename);

	reader.ReadCSV(filename);	//Read data
	Graph* graph = reader.GetGraph();
	map<string, City*>* cities = reader.GetCityList();
	string source = reader.GetRandomCity();
	string sink = reader.GetRandomCity(source);

	//Rest of algorithms here//

	return 0;
}
*/