#include "DataGenerator.h"
#include "Reader.h"

int main() {
	int numCities = 100;
	int minCityNameLength = 5;
	int maxCityNameLength = 7;
	DataGenerator gen(numCities, minCityNameLength, maxCityNameLength);

	gen.GenerateCityNames();
	gen.Debug();

	return 0;
}
