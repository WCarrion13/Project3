#include "DataGenerator.h"

DataGenerator::DataGenerator(int numCities, int minCityNameLength, int maxCityNameLength) {
	this->cityGraph = new Graph;
	this->numCities = numCities;
	this->minCityNameLength = minCityNameLength;
	this->maxCityNameLength = maxCityNameLength;
}

char DataGenerator::GetRandomChar(string type) {
	int typeNum = 0;
	if (type == "num")
		typeNum = 0;
	else if (type == "lc")
		typeNum = 1;
	else if (type == "uc")
		typeNum = 2;
	char c;
	switch (typeNum) {
	case 0:
		c = numbers[rand() % 10];
		break;
	case 1:
		c = lettersLC[rand() % 26];
		break;	
	case 2:
		c = lettersUC[rand() % 26];
	}
	return c;
}

void DataGenerator::Debug() {
	cityGraph->PrintGraph();
}

string DataGenerator::GenerateCityName() {
	int nameType = rand() % 3 + 1;
	int nameLength = Rand(minCityNameLength, maxCityNameLength);
	while (true) {
		string name = "";
		name += GetRandomChar("uc");
		for (int letter = 0; letter < nameLength; letter++)
			name += GetRandomChar("lc");

		switch (nameType) {
		case 1:		//Add beginning string
			name = "City of " + name;
			break;
		case 2:		//Add end string
			name += ends[Rand(1, ends->size())];	
			break;
		case 3:		//No addition
			break;
		}
		if (!cityGraph->Exists(name))	//Check if name already exists
			return name;
	}
}

void DataGenerator::GenerateCities() {
	string from = GenerateCityName();
	string to = GenerateCityName();
	int weight = Rand(minWeight, maxWeight);
	cityGraph->InsertEdge(from, to, weight);	//Generate two starting cities
	cityGraph->InsertEdge(to, from, weight);
	while (cityGraph->GetSize() <= numCities) {		//Generate an additional city
		from = GenerateCityName();
		int numAdjCities = (maxAdjCities > cityGraph->GetSize()) ? maxAdjCities : Rand(minAdjCities, maxAdjCities);	//Ensure adj cities does not exceed existing city count
		set<string> adjCities = {};
		int adjCityIndex = 0;
		for (int city = 0; city < numAdjCities; city++) {	//Generate connections to/from city
			adjCityIndex = Rand(0, cityGraph->GetSize() - 1);
			auto iter = cityGraph->Begin();
			for (int index = 0; index < adjCityIndex; index++)		//Find random city in graph
				iter++;
			to = iter->first;
			if ((to != from) && (adjCities.find(to) == adjCities.end())) {	//Check if adj city found is unique
				weight = Rand(minWeight, maxWeight);
				cityGraph->InsertEdge(from, to, weight);	//Insert two-way connection
				cityGraph->InsertEdge(to, from, weight);
			} else
				city--;
		}
	}
}


void DataGenerator::OutputToCSV(string filename) {
	file.open(filename);
	for (auto city = cityGraph->Begin(); city != cityGraph->End(); city++) {
		int population = Rand(minPopulation, maxPopulation);
		int numShelters = Rand(minNumShelters, maxNumShelters);
		int numAdjCities = city->second.size();

		file << city->first << "," << population << "," << numShelters << ",";	//Print shelter info
		for (int i = 0; i < numShelters; i++) {
			string shelterName = to_string(i);
			int shelterCapacity = Rand(minShelterCapacity, maxShelterCapacity);
			file << shelterName << "," << shelterCapacity << ",";
		}

		file << numAdjCities << ",";	//Print adjacent city info
		for (auto adjCity = city->second.begin(); adjCity != city->second.end(); adjCity++) {
			file << adjCity->first << "," << adjCity->second << ",";
		}
		file << endl;
	}
	file.close();
}
