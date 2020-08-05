//Main
#include <iostream>
#include "DataGenerator.h"
#include "Reader.h"
#include "FordFulkerson.h"
#include "PushRelabel.h"

int main(int argc, const char * argv[]) {
    bool exit = false;
    int inputNum;

        cout << "Welcome to Natural Disaster's Project!" << endl;
    while (!exit) {
        cout << "Please enter one of the following options (e.g. 1): " << endl;
        cout << "[1] Generate random Road Network" << endl;
        cout << "[2] Enter your own parameters" << endl;
        cout << "[3] Generate Max Flow of 100,000 Road Networks" << endl;
        cout << "[4] Exit program" << endl;

        cin >> inputNum;

        if (inputNum == 1) {
            //Set up of random data to process
            int numCities = 100;
            DataGenerator gen(numCities);
            Reader reader;
            string filename = "test.csv";

            gen.GenerateCities();        //Generate random data
            gen.OutputToCSV(filename);
            reader.ReadCSV(filename);    //Read data
            map<string, City*>* cities = reader.GetCityList();
            string source = reader.GetRandomCity();
            string sink = reader.GetRandomCity(source);

            //Create FF object
            FordFulkerson FF_Algo(*cities, source, sink);
            //Create hurricane and PR object
            NetworkPR pushRelabel = NetworkPR(*cities);
            // Create a hurricane

            bool validInput = false;

            while (!validInput) {
                //Choose whether you want to get max flow from FF, PR, or both
                cout << "You've selected Option 1: " << endl;
                cout << "Choose whether you want to get max flow from FF, PR, or both: " << endl;
                cout << "[1] Ford Fulkerson: " << endl;
                cout << "[2] Push Relabel: " << endl;
                cout << "[3] Both: " << endl;
                cout << "[4] Go Back: " << endl;

                //Take in user choice
                cin >> inputNum;

                if (inputNum == 1) {
                    FF_Algo.PrintMaxFlow();

                    //Create Hurricane
                    pushRelabel.decisionMaking(source, sink);
                    //Exit loop
                    validInput = true;
                }
                else if (inputNum == 2) {
                    pushRelabel.printTheMaximumFlow(source, sink);

                    //Create Hurricane
                    pushRelabel.decisionMaking(source, sink);
                    //Exit loop
                    validInput = true;
                }
                else if (inputNum == 3) {
                    FF_Algo.PrintMaxFlow();
                    pushRelabel.printTheMaximumFlow(source, sink);

                    //Create Hurricane
                    pushRelabel.decisionMaking(source, sink);
                    //Exit loop
                    validInput = true;
                }
                else if (inputNum == 4) {
                    validInput = true;
                }
                else {
                    cout << "Invalid Input! Please Try Again" << endl;
                }
            }
        }
        else if (inputNum == 2) {
            //Parameters for road network
            int numCities = 2;
            int minRoadCap = 1;
            int maxRoadCap = 1;
            int minPopulation = 1;
            int maxPopulation = 1;

            cout << "You've selected Option 2: " << endl;

            bool validInput = false;

            //Loop until valid input inserted for number of Cities
            while (!validInput) {
            cout << "Enter the number of cities in the road network (Valid: 5 - 500): " << endl;
            cin >> inputNum;
                if (inputNum >= 5 && inputNum <= 500) {
                    numCities = inputNum;
                    validInput = true;
                }
                else {
                    cout << "Please enter valid input (Valid: 5 - 500): " << endl;
                }

            }
            //Reset valid input bool
            validInput = false;

            //Loop until valid input inserted for minimum roadCap
            while (!validInput) {
            cout << "Enter the minimum possible road capacity in the road network (Valid: 1 - 1000): " << endl;
            cin >> inputNum;
                if (inputNum >= 1 && inputNum <= 1000) {
                    minRoadCap = inputNum;
                    validInput = true;
                }
                else {
                    cout << "Please enter valid input (Valid: 1 - 1000): " << endl;
                }

            }

            //Reset valid input bool
            validInput = false;

            //Loop until valid input inserted for maximum roadCap
            while (!validInput) {
            cout << "Enter the maximum possible road capacity in the road network (Valid: 1000 - 500000): " << endl;
            cin >> inputNum;
                if (inputNum >= 1000 && inputNum <= 500000) {
                    maxRoadCap = inputNum;
                    validInput = true;
                }
                else {
                    cout << "Please enter valid input (Valid: 1000 - 500000): " << endl;
                }

            }

            //Reset valid input bool
            validInput = false;

            //Loop until valid input inserted for minimum populationNum
            while (!validInput) {
            cout << "Enter the minimum possible road capacity in the road network (Valid: 1 - 1000): " << endl;
            cin >> inputNum;
                if (inputNum >= 1 && inputNum <= 1000) {
                    minPopulation = inputNum;
                    validInput = true;
                }
                else {
                    cout << "Please enter valid input (Valid: 1 - 1000): " << endl;
                }

            }

            //Reset valid input bool
            validInput = false;

            //Loop until valid input inserted for maximum populationNum
            while (!validInput) {
            cout << "Enter the minimum possible road capacity in the road network (Valid: 1000 - 20000000): " << endl;
            cin >> inputNum;
                if (inputNum >= 1000 && inputNum <= 20000000) {
                    maxPopulation = inputNum;
                    validInput = true;
                }
                else {
                    cout << "Please enter valid input (Valid: 1 - 20000000): " << endl;
                }

            }
            //Set up of specified parameters to process
            DataGenerator gen(numCities, minRoadCap, maxRoadCap, minPopulation, maxPopulation);
            Reader reader;
            string filename = "test.csv";

            gen.GenerateCities();        //Generate random data
            gen.OutputToCSV(filename);
            reader.ReadCSV(filename);    //Read data
            map<string, City*>* cities = reader.GetCityList();
            string source = reader.GetRandomCity();
            string sink = reader.GetRandomCity(source);

            //Create FF object
            FordFulkerson FF_Algo(*cities, source, sink);
            //Create hurricane and PR object
            NetworkPR pushRelabel = NetworkPR(*cities);
            // Create a hurricane

            validInput = false;

            while (!validInput) {
                //Choose whether you want to get max flow from FF, PR, or both
                cout << "Choose whether you want to get max flow from FF, PR, or both: " << endl;
                cout << "[1] Ford Fulkerson: " << endl;
                cout << "[2] Push Relabel: " << endl;
                cout << "[3] Both: " << endl;
                cout << "[4] Go Back: " << endl;

                //Take in user choice
                cin >> inputNum;

                if (inputNum == 1) {
                    FF_Algo.PrintMaxFlow();

                    //Create Hurricane
                    pushRelabel.decisionMaking(source, sink);
                    //Exit loop
                    validInput = true;
                }
                else if (inputNum == 2) {
                    pushRelabel.printTheMaximumFlow(source, sink);

                    //Create Hurricane
                    pushRelabel.decisionMaking(source, sink);
                    //Exit loop
                    validInput = true;
                }
                else if (inputNum == 3) {
                    FF_Algo.PrintMaxFlow();
                    pushRelabel.printTheMaximumFlow(source, sink);

                    //Create Hurricane
                    pushRelabel.decisionMaking(source, sink);
                    //Exit loop
                    validInput = true;
                }
                else if (inputNum == 4) {
                    validInput = true;
                }
                else {
                    cout << "Invalid Input! Please Try Again" << endl;
                }
            }

        }
        else if (inputNum == 3) {

        }
        else if (inputNum == 4) {
            cout << "Terminating Program. Good Bye!" << endl;
            exit = true;
        }
        else {
            cout << "Invalid input! Please try again." << endl;
        }

    }

    return 0;
}
