#include "Reader.h"

string Reader::GetRandomCity() {
	int index = GetRandInt(0, cityList->size() - 1);
	auto iter = cityList->begin();
	for (int i = 0; i < index; i++)
		iter++;
	return iter->first;	
}

string Reader::GetRandomCity(string exclude) {
	while (true) {
		int index = GetRandInt(0, cityList->size() - 1);
		auto iter = cityList->begin();
		for (int i = 0; i < index; i++)
			iter++;
		if (iter->first != exclude)		//Ensure no duplicates
			return iter->first;
	}
}

string Reader::GetRandomCity(vector<string> exclude) {
	while (true) {
		int index = GetRandInt(0, cityList->size() - 1);
		auto iter = cityList->begin();
		bool duplicate = false;
		for (int i = 0; i < index; i++)
			iter++;
		for (int i = 0; i < exclude.size(); i++) {
			if (iter->first == exclude[i])		//Ensure no duplicates
				duplicate = true;
		}
		if (!duplicate)
			return iter->first;
	}
}

void Reader::AddAdjCities() {	
	for (auto iter = cityList->begin(); iter != cityList->end(); iter++)	
		iter->second->AddAdjCity(&graph->Find(iter->first)->second);
}

void Reader::ReadCSV(string filename) {
	ifstream file(filename);
	string line = "";
	while (getline(file, line))	{	//Read a single line with each loop
		string name, population, numShelters, numAdjCities;	//Read city information
		stringstream ss(line);
		getline(ss, name, ',');
		getline(ss, population, ',');
		City* city = new City(name, stoi(population));
		
		getline(ss, numShelters, ',');		//Read shelter-related information
		for (int shelter = 0; shelter < stoi(numShelters); shelter++) {
			string shelterName;
			string shelterCapacity;
			getline(ss, shelterName, ',');
			getline(ss, shelterCapacity, ',');
			city->AddShelter(shelterName, stoi(shelterCapacity));
		}
		
		getline(ss, numAdjCities, ',');		//Read adjacent city-related information
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
	AddAdjCities();
}