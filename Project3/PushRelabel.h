#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include"Graph.h"
#include"City.h"
using namespace std;
// Initializing a road network including city
class Hurricane
{
    int speed;          // kilometer/hr
    int distance;       // in kilometer
    string category;
public:
    Hurricane(int speed, int distance)
    {
        this->speed = speed;
        this->distance = distance;
        if(speed >= 119 && speed <= 153)
        {
            this->category = "Category 1";
        }
        else if(speed >= 154 && speed <= 177)
        {
            this->category = "Category 2";
        }
        else if(speed >= 178 && speed <= 208 )
        {
            this->category = "Category 3";
        }
        else if(speed >= 209 && speed <= 251)
        {
            this->category = "Category 4";
        }
        else if(speed >= 252)
        {
            this->category = "Category 5";
        }
        else if (speed >= 89 && speed <= 119 )
        {
            this->category = "Tropical storm";
        }

    }
    int getSpeed()
    {
        return speed;
    }
    int getDistance()
    {
        return distance;
    }
    string getTheCategory()
    {
        return category;
    }
    int timeToMakeLandFall() const
    {
        return distance/speed; // in hour
    }

};
struct Road
{
    // To store current flow and capacity of road
    int flow, capacity;
    // An road from--->v has from vertex as from and to vertex as v.
    string from, to;
    Road(int flow, int capacity, string from, string to)
    {
        this->flow = flow;
        this->capacity = capacity;
        this->from = from;
        this->to = to;
    }
};

// Represent a City
class CityPR
{
public:
    int h, e_flow;
    int population;
    int numShelter;
    int shelterCapacity;
    int capacity;
    string name;
    CityPR(int h, int e_flow)
    {
        this->h = h;
        this->e_flow = e_flow;
    }
    CityPR(int h, int e_flow, string name)
    {
        this->name = name;
        this->h = h;
        this->e_flow = e_flow;
    }

    CityPR(int h, int e_flow, int _population, int _numShelter, int _shelterCapacity, string nameCity)
    {
        this->name = nameCity;
        this->shelterCapacity = _shelterCapacity;
        this->numShelter = _numShelter;
        this->population = _population;
        this->capacity = _numShelter * _shelterCapacity;
        this->h = h;
        this->e_flow = e_flow;
    }
};

// To represent a flow network
class NetworkPR
{
    string source; //Source city
    string sink; //Destination city;
    int V = 0;    // No. of city
    // Map the city to integer
    vector<string>cityName;  //Mapping city name into number
    vector<CityPR> city;    // Manipulate the execess flow and the height of each city or node
    vector<CityPR> cityCopy; // This vector is used to copy all the city to a new graph
    vector<Road> road; // This vector is used to store all the edges to implement push and relabel algorithm
    vector<Road> roadNetwork; //This vector is used to store the road network to perform finding city
    // Function to push excess flow from from
    bool push(string from);
    // Function to relabel a vertex from
    void relabel(string from);
    // This function is called to initialize preflow
    void preflow(string source);
    // Function to reverse road
    void updateReverseEdgeFlow(int i, int flow);
    //Hurrican generator

public:
    Hurricane createHurricane();
    NetworkPR(int V);  // Constructor
    NetworkPR (map<string, City*>& roadNetWork); //Construct a new Network
    NetworkPR(const NetworkPR& rhs); // Copy constructor
    NetworkPR& operator=(const NetworkPR& rhs); // copy assignment operator
    ~NetworkPR();
    int matchingCity(string cityName);
    CityPR getCity(string nameCity);

    // function to add an road to graph
    void addRoad(string from, string to, int w);
    // returns maximum flow from s to t
    int getMaxFlow(string from, string to);
    string overFlowVertex(vector<CityPR>& ver, string source, string to);
    void neighboringCity (string name);
    void printTheMaximumFlow(string from, string to, int rate);
    //Intialize the city with population
    void initializeCity (string name, int population, int numShelter, int shelterCapacity);
    //Calculate the time for people to evac
    // float timeTakeToEvac(Hurricane hurricane, string from, string to);
    //Get the list of cities that the current city connect to
    vector <CityPR> connectTo (string name);
    // Get the info of nearby cities that has a way to go over
    void decisionMaking (string from, string to, Hurricane hurricane, int numPeopleEvac);
};
NetworkPR::NetworkPR(int V)
{
    this->V = V;
    //all cities are initialized with 0 height and 0 excess flow
}


int NetworkPR::matchingCity(string name)
{
    auto it = find(cityName.begin(), cityName.end(), name);
    if(it != cityName.end())
    {
        int index = distance(cityName.begin(), it);
        return index;
    }
    else
    {
        return -1;
    }
}



void NetworkPR::addRoad(string u, string v, int capacity)
{
    // flow is initialized with 0 for all road
    road.push_back(Road(0, capacity, u, v));
    roadNetwork.push_back(Road(0,capacity,u,v));
    if(cityName.empty())
    {
        cityName.push_back(u);
        cityName.push_back(v);
    }
    else
    {
        auto it = find(cityName.begin(), cityName.end(), u);
        if(it == cityName.end())
        {
            cityName.push_back(u);
        }
        auto it2 = find(cityName.begin(), cityName.end(), v);
        if(it2 == cityName.end())
        {
            cityName.push_back(v);
        }
    }
}

void NetworkPR::preflow(string source)
{
    // Making h of source City equal to no. of vertices
    // Height of other vertices is 0.
    int s = matchingCity(source);
    city[s].h = city.size();
    //
    for (int i = 0; i < road.size(); i++)
    {
        // If current road goes from source
        if (matchingCity(road[i].from) == s)
        {
            // Flow is equal to capacity
            road[i].flow = road[i].capacity;
            //int roadFlow = road[i].flow;
            // Initialize excess flow for adjacent v
            //int cityE_flow = city[matchingCity(road[i].to)].e_flow;
            city[matchingCity(road[i].to)].e_flow += road[i].flow;
            //int cityE_flow2 = city[matchingCity(road[i].to)].e_flow;

            // Add an road from v to s in residual graph with
            // capacity equal to 0
            road.push_back(Road(-road[i].flow, 0, road[i].to, source));
        }
    }
}

// returns index of overflowing City
string NetworkPR::overFlowVertex(vector<CityPR>& ver, string s, string t)
{
    for(int i = 0; i < ver.size(); i++)
    {
        string cityNameToCompare = cityName[i];
        if(cityNameToCompare!= s && cityNameToCompare!= t && ver[i].e_flow>0)
        {
            return cityNameToCompare;
        }
    }
    return "";
}

// Update reverse flow for flow added on ith Edge
void NetworkPR::updateReverseEdgeFlow(int i, int flow)
{
    int u = matchingCity(road[i].to);
    int v = matchingCity(road[i].from);

    for (int j = 0; j < road.size(); j++)
    {
        if (matchingCity(road[j].to) == v && matchingCity(road[j].from) == u)
        {
            road[j].flow -= flow;
            return;
        }
    }
    // adding reverse Edge in residual graph
    Road e = Road(0, flow, road[i].to, road[i].from);
    road.push_back(e);
}

// To push flow from overflowing vertex from
bool NetworkPR::push(string u)
{
    // Traverse through all edges to find an adjacent (of from)
    // to which flow can be pushed
    for (int i = 0; i < road.size(); i++)
    {
        // Checks from of current road is same as given
        // overflowing vertex
        if (road[i].from == u)
        {
            // if flow is equal to capacity then no push
            // is possible
            if (road[i].flow == road[i].capacity)
                continue;

            // Push is only possible if height of adjacent
            // is smaller than height of overflowing vertex
            if (city[matchingCity(u)].h > city[matchingCity(road[i].to)].h)
            {
                // Flow to be pushed is equal to minimum of
                // remaining flow on road and excess flow.
                int flow = min(road[i].capacity - road[i].flow, city[matchingCity(u)].e_flow);
                // Reduce excess flow for overflowing vertex
                city[matchingCity(u)].e_flow -= flow;
                // Increase excess flow for adjacent
                city[matchingCity(road[i].to)].e_flow += flow;
                // Add residual flow (With capacity 0 and negative flow)
                road[i].flow += flow;
                updateReverseEdgeFlow(i, flow);
                return true;
            }
        }
    }
    return false;
}

// function to relabel vertex from
void NetworkPR::relabel(string u)
{
    // Initialize minimum height of an adjacent
    int minHeight = INT_MAX;
    // Find the adjacent with minimum height
    for (int i = 0; i < road.size(); i++)
    {
        if (road[i].from == u)
        {
            // if flow is equal to capacity then no
            // relabeling
            if (road[i].flow == road[i].capacity)
                continue;

            // Update minimum height
            if (city[matchingCity(road[i].to)].h < minHeight)
            {
                minHeight = city[matchingCity(road[i].to)].h;

                // updating height of from
                city[matchingCity(u)].h = minHeight + 1;
            }
        }
    }
}

// main function for printing maximum flow of graph
int NetworkPR::getMaxFlow(string s, string t)
{
    preflow(s);

    // loop untill none of the City is in overflow
    while (overFlowVertex(city, s, t) != "")
    {
        string u = overFlowVertex(city, s, t);
        bool testValue = push(u);
        if (!testValue)
        {
            relabel(u);
        }
    }
    // city.back() returns last City, whose e_flow will be final maximum flow
    //int cityE_flow = city[matchingCity(t)].e_flow;
    return city[matchingCity(t)].e_flow;
}

void NetworkPR::neighboringCity(string name) {

    for(int i = 0; i< road.size(); i++)
    {
        //City that connect to city
        if(road[i].from == name)
        {
            cout<<"City "<< name<< " connects to city "<< road[i].to<<endl;
        }

    }
    for(int i = 0; i< road.size(); i++)
    {
        // City that connect from other city
        if(road[i].to == name)
        {
            cout<<"City "<< road[i].from<< " connects to city "<< name <<endl;
        }
    }
}

void NetworkPR::initializeCity(string cityName, int population, int numShelter, int shelterCapacity) {
    city.push_back(CityPR(0,0, population, numShelter, shelterCapacity, cityName));
    cityCopy = city;
}

void NetworkPR::printTheMaximumFlow(string from, string to, int rate)
{
    cout<< "The maximum amount of people that can evacuate to "<< to << " from" << from << " is: " << rate << "/hour" << endl;
}

Hurricane NetworkPR::createHurricane()
{
    srand(time(NULL));
    int randomSpeed = rand() % 200 + 89;
    int distance  = rand()% 483 + 241;
    return Hurricane(randomSpeed, distance);
}

/*float NetworkPR::timeTakeToEvac(Hurricane hurricane, string from, string to) {
    CityPR runAway = getCity(from);
    int population = runAway.population;
    int numberPeopleEvacPerHour = getMaxFlow(from, to); //
    float totalTimeTakeToEvac = float(population)/numberPeopleEvacPerHour;
    return totalTimeTakeToEvac;
}*/

void NetworkPR::decisionMaking(string from, string to, Hurricane hurricane, int numPeopleEvacPerHour) {

    CityPR runAway = getCity(from);
    CityPR runTo = getCity(to);
    int populationCity = runAway.population;
    float totalTimeTakeToEvac = float(populationCity)/numPeopleEvacPerHour;
    int timeMakeLandFall = hurricane.timeToMakeLandFall();
    cout<<"The hurricane speed is "<< hurricane.getSpeed()<<endl;
    cout<<"It falls into "<< hurricane.getTheCategory()<<endl;
    if(hurricane.getTheCategory() == "Category 5" || hurricane.getTheCategory() == "Category 4" || hurricane.getTheCategory() == "Category 3" )
    {
        cout<<"DANGER: THE HURRICANE IS DESTRUCTIVE.\nREQUIRE REPAIR IN ADVANCE";
        if(timeMakeLandFall < totalTimeTakeToEvac)
        {
            cout<<"NEEDS TO EVACUATE THE SYSTEM ASAP\n";
            int totalCapacityCityCanHold = runTo.capacity;
            cout<<"The capacity that "<< runTo.name<< " can hold is "<< totalCapacityCityCanHold<<endl;
            int leftOut = populationCity - totalCapacityCityCanHold;
            cout<<"Number of people will be left out is "<< leftOut<<endl;
            if(populationCity > totalCapacityCityCanHold)
            {
                vector <CityPR> adjCity = connectTo(to);
                cout<<"City "<<runTo.name<<" shelter capacity is compromised.\nList of nearby cities that people can evacuate.\n";
                for(CityPR city : adjCity)
                {
                    if(city.capacity==0)
                    {
                        cout << city.name << " doesn't have a shelter. Avoid at all cost";
                        continue;
                    }
                    cout<<"Name: "<<city.name<<"Total capacity: "<<city.capacity<<endl;
                }
            }
        }
    }
    else
    {
        cout<<"NO NEED FOR EVACUATION\nJUST DON'T BE A FLORIDA MAN";
    }

}

CityPR NetworkPR::getCity(string nameCity) {
    for(auto it = cityCopy.begin(); it != cityCopy.end(); it++)
    {
        if (it->name == nameCity) {
            return *it;
        }
    }
    return CityPR(0,0);
}

vector<CityPR> NetworkPR::connectTo(string name) {
    vector<CityPR>connect;
    for(int i = 0; i< road.size(); i++)
    {
        //City that connect to city
        if(road[i].from == name)
        {
            for(auto it = city.begin(); it!= city.end(); it++)
            {
                if(it->name == road[i].to)
                {
                    connect.push_back(*it);
                }
            }
        }
    }
    return connect;
}

NetworkPR::NetworkPR(const NetworkPR &rhs) {
    V = rhs.V;
    cityName = rhs.cityName;
    city = rhs.cityCopy;
    road = rhs.roadNetwork;
    roadNetwork = rhs.roadNetwork;

}
NetworkPR& NetworkPR::operator=(const NetworkPR &rhs) {
    V = rhs.V;
    cityName = rhs.cityName;
    city = rhs.cityCopy;
    road = rhs.roadNetwork;
    roadNetwork = rhs.roadNetwork;
    return *this;
}

NetworkPR::~NetworkPR()
{
    V = 0;
    cityName.clear();
    city.clear();
    road.clear();
    roadNetwork.clear();
}

NetworkPR::NetworkPR(map<string, City *>& roadNetWork) {

    for (auto it = roadNetWork.begin(); it != roadNetWork.end(); it++) {
        City* currentCity = it->second;
        //CityPR cityInfo = CityPR(0, 0, currentCity->GetPopulation(), (int) currentCity->GetShelters().size(), 1000, it->first);
        initializeCity(it->first, currentCity->GetPopulation(),(int)currentCity->GetShelters().size(), 10000 );
        V++;
        //cityName.push_back(currentCity->GetName());
        //city.push_back(cityInfo);
        map<string, int>* adjCities =  currentCity->GetAdjCities();
        for (auto it2 = (*adjCities).begin(); it2 != (*adjCities).end(); it2++) {
            addRoad(it->first,it2->first,it2->second);
            //Road currentRoad = Road(0, it2->second, it->first, it2->first);
           // road.push_back(currentRoad);
        }
    }

}

