#include "DataGenerator.h"
#include "Reader.h"

int main() {
	int numCities = 10000;
	int minCityNameLength = 5;
	int maxCityNameLength = 7;
	DataGenerator gen(numCities, minCityNameLength, maxCityNameLength);

	gen.GenerateCities();
	gen.OutputToCSV();
	return 0;
}
