#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

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
class City
{
public:
    int h, e_flow;
    int population;
    int numShelter;
    int shelterCapacity;
    int capacity;
    string name;
    City(int h, int e_flow)
    {
        this->h = h;
        this->e_flow = e_flow;
    }
    City(int h, int e_flow, string name)
    {
        this->name = name;
        this->h = h;
        this->e_flow = e_flow;
    }
    /* City(int h, int e_flow, int _population, string name)
     {
         this->population = _population;
         this->h = h;
         this->e_flow = e_flow;
         this->name = name;
     }*/
    City(int h, int e_flow, int _population, int _numShelter, int _shelterCapacity, string nameCity)
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
class Graph
{
    //Nested class to get hurricane
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
        int timeToMakeLandFall()
        {
            return distance/speed; // in hour
        }

    };

    int V;    // No. of city
    // Map the city to integer
    vector<string>cityName;
    vector<City> city;
    vector<Road> road;
    // Function to push excess flow from from
    bool push(string from);
    // Function to relabel a vertex from
    void relabel(string from);
    // This function is called to initialize preflow
    void preflow(string source);
    // Function to reverse road
    void updateReverseEdgeFlow(int i, int flow);
    //Hurrican generator
    Hurricane createHurricane();
public:

    Graph(int V);  // Constructor
    int matchingCity(string cityName);
    City getCity(string nameCity);
    //void pairingCityWithNumber();
    // function to add an road to graph
    void addRoad(string from, string to, int w);
    // returns maximum flow from s to t
    int getMaxFlow(string from, string to);
    string overFlowVertex(vector<City>& ver, string source, string to);
    void neighboringCity (string name);
    void printTheMaximumFlow(string from, string to);
    //Intialize the city with population
    void initializeCity (string name, int population, int numShelter, int shelterCapacity);
    //Calculate the time for people to evac
    float timeTakeToEvac(Hurricane hurricane, City city, string from, string to);
    // Get the info of nearby cities that has a way to go over
    void decisionMaking (float timeEvac, City city, Hurricane hurricane);

};

int Graph::matchingCity(string name)
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

Graph::Graph(int V)
{
    this->V = V;
    // all cities are initialized with 0 height and 0 excess flow
}

void Graph::addRoad(string u, string v, int capacity)
{
    // flow is initialized with 0 for all road
    road.push_back(Road(0, capacity, u, v));

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

void Graph::preflow(string source)
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
            int roadFlow = road[i].flow;
            // Initialize excess flow for adjacent v
            int cityE_flow = city[matchingCity(road[i].to)].e_flow;
            city[matchingCity(road[i].to)].e_flow += road[i].flow;
            int cityE_flow2 = city[matchingCity(road[i].to)].e_flow;

            // Add an road from v to s in residual graph with
            // capacity equal to 0
            road.push_back(Road(-road[i].flow, 0, road[i].to, source));
        }
    }
}

// returns index of overflowing City
string Graph::overFlowVertex(vector<City>& ver, string s, string t)
{
    for(int i = 0; i < ver.size(); i++)
    {
        string cityNameToCompare = cityName[i];
        //cout<<"e_flow of vertex "<<cityNameToCompare<<ver[i].e_flow<<endl;
        int verE_flow = ver[i].e_flow;
        if(cityNameToCompare!= s && cityNameToCompare!= t && ver[i].e_flow>0)
        {
            return cityNameToCompare;
        }
    }
    return "";
}

// Update reverse flow for flow added on ith Edge
void Graph::updateReverseEdgeFlow(int i, int flow)
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
bool Graph::push(string u)
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
void Graph::relabel(string u)
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
int Graph::getMaxFlow(string s, string t)
{
    preflow(s);

    // loop untill none of the City is in overflow
    while (overFlowVertex(city, s, t) != "")
    {
        string u = overFlowVertex(city,s ,t);
        bool testValue = push(u);
        if (!testValue)
        {
            relabel(u);
        }
    }
    // city.back() returns last City, whose
    // e_flow will be final maximum flow
    int cityE_flow = city[matchingCity(t)].e_flow;
    return city[matchingCity(t)].e_flow;
}

void Graph::neighboringCity(string name) {

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

void Graph::initializeCity(string cityName, int population, int numShelter, int shelterCapacity) {
    city.push_back(City(0,0, population, numShelter, shelterCapacity, cityName));
}

void Graph::printTheMaximumFlow(string from, string to)
{
    int rate = getMaxFlow(from,to);
    cout<< "The maximum people that people can evacuate to city  "<< to << " from"<< " is: " << rate<< "/hour";
    //int numPeopleCanStayInCity = city[matchingCity(from)].capacity;
    //cout<< "The maximum number of people can stay in the city is "<< numPeopleCanStayInCity<<endl;
}

Graph::Hurricane Graph::createHurricane()
{
    srand(time(NULL));
    int randomSpeed = rand() % 200 + 89;
    int distance  = rand()% 483 + 241;
    return Hurricane(randomSpeed, distance);
}

float Graph::timeTakeToEvac(Graph::Hurricane hurricane, City city, string from, string to) {
    int population = city.population; // get the city population
    int numberPeopleEvacPerHour = getMaxFlow(from, to); //
    int timeLandFall = hurricane.timeToMakeLandFall();
    float timeToTakePeopleEvac = float(population)/numberPeopleEvacPerHour;
    return timeToTakePeopleEvac;
}

void Graph::decisionMaking(float timeEvac, City city, Hurricane hurricane) {

}

City Graph::getCity(string nameCity) {
    for(auto it = city.begin(); it != city.end(); it++)
    {
        if (it->name == nameCity) {
            return *it;
        }
    }
    return City(0,0);
}

// Driver program to test above functions
/*
int main()
{
    int numCity = 6;
    int population, numShelter, shelterCapacity;
    string nameCity;
    Graph g(numCity);

    for(int i = 0; i< numCity; i++)
    {
        cin>>nameCity;
        cin>>population;
        cin>>numShelter;
        cin>>shelterCapacity;
        //g.initializeCity(nameCity, population, numShelter, shelterCapacity);
        g.initializeCity(nameCity, population, numShelter, shelterCapacity);
    }

    // Creating above shown flow network
    g.addRoad("a", "b", 16);
    g.addRoad("a", "c", 13);
    g.addRoad("b", "c", 10);
    g.addRoad("c", "b", 4);
    g.addRoad("b", "d", 12);
    g.addRoad("c", "e", 14);
    g.addRoad("d", "c", 9);
    g.addRoad("d", "f", 20);
    g.addRoad("e", "d", 7);
    g.addRoad("e", "f", 4);
    // Initialize source and sink
    string s = "a", t = "f";
    cout << "Maximum flow is " << g.getMaxFlow(s,t);
    cout<<endl;
    g.neighboringCity("a");
    City a = g.getCity("a");
    cout<<a.population;
    cout<<endl;
    //g.printAllEdges();
    return 0;
}
*/
