#include "DataGenerator.h"
#include "Reader.h"

int main() {
	int numCities = 10000;
	int minCityNameLength = 5;
	int maxCityNameLength = 7;
	DataGenerator gen(numCities, minCityNameLength, maxCityNameLength);
	Reader reader;
	string filename = "test.csv";

	gen.GenerateCities();		//Generate random data
	gen.OutputToCSV(filename);

	reader.ReadCSV(filename);	//Read data
	Graph* graph = reader.GetGraph();
	map<string, City*>* cities = reader.GetCityList();

	//Rest of algorithms here//





	return 0;
}
