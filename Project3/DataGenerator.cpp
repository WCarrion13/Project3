#include "DataGenerator.h"

DataGenerator::DataGenerator(int numCities) {
	cityGraph = new Graph;
	this->numCities = numCities;

	prefix.push_back("City of ");

	suffix.push_back("ville");
	suffix.push_back("town");
	suffix.push_back("land");
	suffix.push_back("ington");
	suffix.push_back("ford");
	suffix.push_back("ayton");
	suffix.push_back("ester");
	suffix.push_back("ton");
	suffix.push_back("son");
	suffix.push_back("urn");

	limits["cityName"] = make_pair(5, 7);				//Generate various variable limits
	limits["adjCities"] = make_pair(1, 3);
	limits["roadCapacity"] = make_pair(1, 10);
	limits["population"] = make_pair(10000, 1000000);
	limits["shelters"] = make_pair(0, 3);
	limits["shelterCapacity"] = make_pair(1000, 10000);
}

string DataGenerator::GenerateCityName() {
	int nameType = GetRandInt(1,3);		//Select name template type
	int nameLength = GetRandInt(limits["cityName"]);
	while (true) {
		string name = "";
		name += GetUC();
		for (int letter = 0; letter < nameLength; letter++)
			name += GetLC();

		if (nameType == 1)	
			name = prefix[GetRandInt(0, prefix.size() - 1)] + name;		//Add beginning string
		else if (nameType == 2)
			name += suffix[GetRandInt(0, suffix.size() - 1)];			//Add end string

		if (!cityGraph->Exists(name))	//If name does not already exist, pass to function output
			return name;
	}
}

void DataGenerator::GenerateCities() {
	string from = GenerateCityName();
	string to = GenerateCityName();
	int weight = GetRandInt(limits["roadCapacity"]);
	cityGraph->InsertEdge(from, to, weight);		//Generate two starting cities
	cityGraph->InsertEdge(to, from, weight);
	while (cityGraph->GetSize() < numCities) {		//Generate "numCities" additional cities
		from = GenerateCityName();
		int numAdjCities = (limits["adjCities"].second > cityGraph->GetSize()) ? cityGraph->GetSize() : GetRandInt(limits["adjCities"]);	//Ensure adj cities does not exceed existing city count
		set<string> adjCities = {};
		int adjCityIndex = 0;
		for (int city = 0; city < numAdjCities; city++) {			//Generate connections to/from city
			adjCityIndex = GetRandInt(0, cityGraph->GetSize() - 1);
			auto iter = cityGraph->Begin();
			for (int index = 0; index < adjCityIndex; index++)		//Find random city in graph
				iter++;
			to = iter->first;
			if ((to != from) && (adjCities.find(to) == adjCities.end())) {	//Check if adj city found is unique
				weight = GetRandInt(limits["roadCapacity"]);
				cityGraph->InsertEdge(from, to, weight);	//Insert two-way connection
				cityGraph->InsertEdge(to, from, weight);
				adjCities.insert(to);
			} else
				city--;
		}
	}
}

void DataGenerator::OutputToCSV(string filename) {
	ofstream file(filename, ios_base::out);
	for (auto city = cityGraph->Begin(); city != cityGraph->End(); city++) {
		int population = GetRandInt(limits["population"]);
		int numShelters = GetRandInt(limits["shelters"]);
		int numAdjCities = city->second.size();

		file << city->first << "," << population << "," << numShelters << ",";	//Print shelter info
		for (int i = 0; i < numShelters; i++) {
			string shelterName = "Shelter " + to_string(i);
			int shelterCapacity = GetRandInt(limits["shelterCapacity"]);
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