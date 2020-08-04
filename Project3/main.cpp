//Main
#pragma  once
#include <iostream>
#include "DataGenerator.h"
#include "Reader.h"
#include "FordFulkerson.h"
#include "PushRelabel.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";

    int numCities = 10;
    DataGenerator gen(numCities);
    Reader reader;
    string filename = "test.csv";

    gen.GenerateCities();        //Generate random data
    gen.OutputToCSV(filename);
    reader.ReadCSV(filename);    //Read data
    //Graph* graph = reader.GetGraph();
    map<string, City*>* cities = reader.GetCityList();
    string source = reader.GetRandomCity();
    string sink = reader.GetRandomCity(source);


    //Rest of algorithms here//
    FordFulkerson var1(*cities, source, sink);

    int var = var1.maxFlow();
    //var1.PrintGraph();

    cout << endl;

    cout << "Max flow is: " << var << endl;
    cout<<"hello\n";
    NetworkPR pushRelabel = NetworkPR(*cities);

    pushRelabel.printTheMaximumFlow(source, sink);
    // Create a hurricane
    Hurricane Irma = pushRelabel.createHurricane();
    float totalTimeToEvac = pushRelabel.timeTakeToEvac(Irma, source, sink);
    pushRelabel.decisionMaking(totalTimeToEvac, source, sink, Irma);
    return 0;
}
