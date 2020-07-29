#include "DataGenerator.h"

DataGenerator::DataGenerator(int numCities, int minCityNameLength, int maxCityNameLength) {
	this->cityList = new set<string>;
	this->numCities = numCities;
	this->minCityNameLength = minCityNameLength;
	this->maxCityNameLength = maxCityNameLength - minCityNameLength + 1;
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
	for (auto city = cityList->begin(); city != cityList->end(); city++)
		cout << *city << endl;
}

void DataGenerator::GenerateCityNames() {
	for (int city = 0; city < numCities; city++) {
		int nameType = rand() % 3 + 1;
		int nameLength = rand() % maxCityNameLength + minCityNameLength;
		while (true) {
			string name = "";
			name += GetRandomChar("uc");
			for (int letter = 0; letter < nameLength; letter++)
				name += GetRandomChar("lc");

			switch (nameType) {
			case 1:
				name = "City of " + name;
				break;
			case 2:
				name += ends[rand() % ends->size() + 1];
				break;
			case 3:
				break;
			}
			if (cityList->find(name) == cityList->end()) {
				cityList->insert(name);
				break;
			}
		}
	}
}

void DataGenerator::GenerateCityAttributes() {

}
