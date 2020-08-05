//Main
#include <iostream>
#include "DataGenerator.h"
#include "Reader.h"
#include "FordFulkerson.h"
#include "PushRelabel.h"

int main(int argc, const char * argv[]) {

    //Variable to turn off program
    bool exit = false;
    //Keep track of if we want to create hurricane senario
    bool hurrEnable = true;

    int inputNum;

        cout << "Welcome to Natural Disaster's Project!" << endl;
    while (!exit) {
        cout << "Please enter one of the following options (e.g. 1): " << endl;
        cout << "[1] Generate random Road Network" << endl;
        cout << "[2] Enter your own parameters" << endl;
        cout << "[3] Generate Max Flow of 10,000 Road Networks" << endl;
        cout << "[4] Toggle Hurricane output" << endl;
        cout << "[5] Exit program" << endl;

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
            //Create PR object
            NetworkPR pushRelabel = NetworkPR(*cities);

            bool validInput = false;

            while (!validInput) {
                //Choose whether you want to get max flow from FF, PR, or both
                cout << "You've selected Option 1: " << endl;
                cout << "Choose whether you want to get max flow from FF, PR, or both: " << endl;
                cout << "[1] Ford Fulkerson: " << endl;
                cout << "[2] Push Relabel: " << endl;
                cout << "[3] Both: " << endl;
                cout << "[4] Main menu: " << endl;
                cout << endl;

                //Take in user choice
                cin >> inputNum;

                if (inputNum == 1) {
                    FF_Algo.PrintMaxFlow();
                    cout << endl;
                    //Create Hurricane
                    if (hurrEnable == true) {
                        pushRelabel.decisionMaking(source, sink);
                    }

                    //Exit loop
                    validInput = true;
                }
                else if (inputNum == 2) {
                    pushRelabel.printTheMaximumFlow(source, sink);
                    cout << endl;
                    //Create Hurricane
                    if (hurrEnable == true) {
                        pushRelabel.decisionMaking(source, sink);
                    }

                    //Exit loop
                    validInput = true;
                }
                else if (inputNum == 3) {
                    //Max evacuation rate
                    cout << "FF: ";
                    FF_Algo.PrintMaxFlow();
                    cout << "PR: ";
                    pushRelabel.printTheMaximumFlow(source, sink);
                    cout << endl;
                    //Create Hurricane
                    if (hurrEnable == true) {
                        pushRelabel.decisionMaking(source, sink);
                    }

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
            cout << "Enter the number of cities in the road network (Valid: 5 - 200): " << endl;
            cin >> inputNum;
                if (inputNum >= 5 && inputNum <= 200) {
                    numCities = inputNum;
                    validInput = true;
                }
                else {
                    cout << "Please enter valid input (Valid: 5 - 200): " << endl;
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
            cout << "Enter the maximum possible road capacity in the road network (Valid: 1 - 500000): " << endl;
            cin >> inputNum;
                if (inputNum >= minRoadCap && inputNum >= 1 && inputNum <= 500000) {
                    maxRoadCap = inputNum;
                    validInput = true;
                }
                else {
                    cout << "Please enter valid input (Valid: 1 - 500000) and can't be smaller than minimum road capacity: " << endl;
                }

            }

            //Reset valid input bool
            validInput = false;

            //Loop until valid input inserted for minimum populationNum
            while (!validInput) {
            cout << "Enter the minimum possible population for the cities (Valid: 1 - 1000): " << endl;
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
            cout << "Enter the maximum possible population for the cities (Valid: 1 - 20000000): " << endl;
            cin >> inputNum;
                if (inputNum >= minPopulation && inputNum >= 1 && inputNum <= 20000000) {
                    maxPopulation = inputNum;
                    validInput = true;
                }
                else {
                    cout << "Please enter valid input (Valid: 1 - 20000000) and can't be smaller than minimum population: " << endl;
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
            //Create PR object
            NetworkPR pushRelabel = NetworkPR(*cities);
            // Create a hurricane

            validInput = false;

            while (!validInput) {
                //Choose whether you want to get max flow from FF, PR, or both
                cout << "Choose whether you want to get max flow from FF, PR, or both: " << endl;
                cout << "[1] Ford Fulkerson: " << endl;
                cout << "[2] Push Relabel: " << endl;
                cout << "[3] Both: " << endl;
                cout << "[4] Main menu: " << endl;

                //Take in user choice
                cin >> inputNum;

                if (inputNum == 1) {
                    FF_Algo.PrintMaxFlow();
                    cout << endl;
                    //Create Hurricane
                    if (hurrEnable == true) {
                        pushRelabel.decisionMaking(source, sink);
                    }

                    //Exit loop
                    validInput = true;
                }
                else if (inputNum == 2) {
                    pushRelabel.printTheMaximumFlow(source, sink);
                    cout << endl;
                    //Create Hurricane
                    if (hurrEnable == true) {
                        pushRelabel.decisionMaking(source, sink);
                    }

                    //Exit loop
                    validInput = true;
                }
                else if (inputNum == 3) {
                    //Max evacuation rate
                    cout << "FF: ";
                    FF_Algo.PrintMaxFlow();
                    cout << "PR: ";
                    pushRelabel.printTheMaximumFlow(source, sink);
                    cout << endl;
                    //Create Hurricane
                    if (hurrEnable == true) {
                        pushRelabel.decisionMaking(source, sink);
                    }

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

            bool onlyFF = false;
            bool onlyPR = false;
            bool both = false;

            bool validInput = false;

            while (!validInput) {
                cout << "Choose whether you want to get max flow from FF, PR, or both: " << endl;
                cout << "[1] Ford Fulkerson: " << endl;
                cout << "[2] Push Relabel: " << endl;
                cout << "[3] Both: " << endl;
                cout << "[4] Main menu: " << endl;

                cin >> inputNum;

                if (inputNum == 1) {
                    onlyFF = true;
                    validInput = true;
                }
                else if (inputNum == 2) {
                    onlyPR = true;
                    validInput = true;
                }
                else if (inputNum == 3) {
                    both = true;
                    validInput = true;
                }
                else if (inputNum == 4) {
                    validInput = true;
                }
                else {
                    cout << "Invalid Input! Please Try Again" << endl;
                    cout << endl;
                }
            }

            if (onlyFF == true || onlyPR == true || both == true) {
                cout << "Generating the Max Flow of 10,000 road networks each with 10 cities: " << endl;
                cout << endl;

                int maxNum = 10000;

                for (int i = 0; i < maxNum; i++) {
                    int numCities = 10;
                    DataGenerator gen(numCities);
                    Reader reader;
                    string filename = "test.csv";

                    gen.GenerateCities();        //Generate random data
                    gen.OutputToCSV(filename);
                    reader.ReadCSV(filename);    //Read data
                    map<string, City*>* cities = reader.GetCityList();
                    string source = reader.GetRandomCity();
                    string sink = reader.GetRandomCity(source);

                    if (onlyFF == true || both == true) {
                        //Create FF object
                        FordFulkerson FF_Algo(*cities, source, sink);
                        //Print max flow
                        cout << "FF: ";
                        FF_Algo.PrintMaxFlow();
                    }
                    if (onlyPR == true || both == true) {
                        //Create PR object
                        NetworkPR pushRelabel = NetworkPR(*cities);
                        //Print max flow
                        cout << "PR: ";
                        pushRelabel.printTheMaximumFlow(source, sink);
                    }
                    cout << endl;
                }
            }

        }

        else if (inputNum == 4) {
            if (hurrEnable == true) {
                hurrEnable = false;
                cout << "Turned Off hurricane scenario!" << endl;
                cout << endl;
            }
            else {
                hurrEnable = true;
                cout << "Turned On hurricane scenario!" << endl;
                cout << endl;
            }
        }
        else if (inputNum == 5) {
            cout << "Terminating Program. Good Bye!" << endl;
            exit = true;
        }
        else {
            cout << "Invalid input! Please try again." << endl;
        }

    }

    return 0;
}
