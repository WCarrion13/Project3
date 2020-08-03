#include "Reader.h"

string Reader::GetRandomCity() {
	int index = GetRandInt(0, cityList->size() - 1);
	auto iter = cityList->begin();
	for (int i = 0; i < index; i++)		//Find random city in graph
		iter++;
	return iter->first;
}

void Reader::AddCities() {
	for (auto iter = cityList->begin(); iter != cityList->end(); iter++)	//Add adj city map to each city for eaasy access
		iter->second->AddAdjCity(&graph->Find(iter->first)->second);
}

void Reader::ReadCSV(string filename) {
	ifstream file(filename);
	string line = "";
	while (getline(file, line))	{
		string name;
		string population;
		string numShelters;
		string numAdjCities;
		stringstream ss(line);
		getline(ss, name, ',');
		getline(ss, population, ',');
		City* city = new City(name, stoi(population));
		
		getline(ss, numShelters, ',');
		for (int shelter = 0; shelter < stoi(numShelters); shelter++) {
			string shelterName;
			string shelterCapacity;
			getline(ss, shelterName, ',');
			getline(ss, shelterCapacity, ',');
			city->AddShelter(shelterName, stoi(shelterCapacity));
		}
		
		getline(ss, numAdjCities, ',');
		for (int adjCity = 0; adjCity< stoi(numAdjCities); adjCity++) {
			string adjCityName;
			string adjCityRoadCapacity;
			getline(ss, adjCityName, ',');
			getline(ss, adjCityRoadCapacity, ',');
			graph->InsertEdge(name, adjCityName, stoi(adjCityRoadCapacity));
			graph->InsertEdge(adjCityName, name, stoi(adjCityRoadCapacity));
		}
		(*cityList)[name] = city;
	}
	AddCities();
}