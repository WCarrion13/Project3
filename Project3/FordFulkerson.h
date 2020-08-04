#pragma once

#include<iostream>
#include<map>
#include"Graph.h"
#include"City.h"
#include<string>
#include<vector>
#include<queue>
using namespace std;


class FordFulkerson {
private:
    class Edge {
    public:
        string to;
        int remainingCap;
        int totalCap;
        int flow;

    public:
        Edge(int flow, string to, int totalCap) {
            this->flow = flow;
            this->to = to;
            remainingCap = totalCap;
            this->totalCap = totalCap;
        }
    };

    map<string, vector<Edge> > originalGraph;
    string source;
    string destination;

public:
    FordFulkerson(Graph &roadNetwork, string source, string destination) {
        //Declare out source and destination nodes;
        this->source = source;
        this->destination = destination;

        //Recreate the original graph with flow added
        for (auto it = roadNetwork.Begin(); it != roadNetwork.End(); it++) {
            vector<Edge> edges;
            for (auto iter = it->second.begin(); iter != it->second.end(); iter++) {
                Edge edge(0, iter->first, iter->second);

                edges.push_back(edge);
            }
            originalGraph[it->first] = edges;
        }
    }

    FordFulkerson(map<string, City*>& roadNetwork, string source, string destination) {
        //Declare out source and destination nodes;
        this->source = source;
        this->destination = destination;

        for (auto it = roadNetwork.begin(); it != roadNetwork.end(); it++) {
            vector<Edge> edges;
            City* currentCity = it->second;
            map<string, int>* adjCities = currentCity->GetAdjCities();

            for (auto it2 = (*adjCities).begin(); it2 != (*adjCities).end(); it2++) {
                Edge edge(0, it2->first, it2->second);

                edges.push_back(edge);
            }
            originalGraph[it->first] = edges;
        }

    }


    map<string, pair<string, int> > BFS() {
        //Storing the path we took from source to dest node. Organized as map<string to, string from>.
        map<string, pair<string, int> > path;
        //Create a map that keeps track of nodes we have visited
        map<string, bool> visited;
        visited[source] = true;
        //Create a queue that will help us do out BFS
        queue<string> que;
        //Start by pushing source node into the queue
        que.push(source);

        //While the queue is not empty update the path we are taking towards destination node
        while(!que.empty()) {
            //Variable to keep track of current city, then dequeue front node
            string currentCity = que.front();
            que.pop();
            // return path if we have reached destination node. Otherwise continue updating the path
            if(currentCity == destination) {
                return path;
            }
            else {
                visited[currentCity] = true;

                vector<Edge> tempEdges = originalGraph[currentCity];
                //cout << tempEdges.at(0).remainingCap << endl;

                for (int i = 0; i < tempEdges.size(); i++) {
                    string to = tempEdges.at(i).to;
                    int remainCap = tempEdges.at(i).remainingCap;

                    if((remainCap > 0) && (visited.find(to) == visited.end())) {
                        que.push(to);
                        path[to] = {currentCity, i};
                    }
                }
            }

        }
        //We only reach here if we are returning a path that doesn't contain the destination node
        return path;
    }

    int UpdateGraph (map<string, pair<string, int> >& path) {
        //New graph we will use
        map<string, vector<Edge> > updatedGraph = originalGraph;

        int pathFlow = 0;
        int minRemainCap = 999999999;

        string childCity = destination;
        string parentCity = path[childCity].first;
        int parentIndex = path[childCity].second;

        while(childCity != source) {

            Edge tempEdge = updatedGraph[parentCity].at(parentIndex);

            if (tempEdge.remainingCap < minRemainCap) {
                minRemainCap = tempEdge.remainingCap;
            }

            childCity = parentCity;

            if (childCity != source) {
            parentCity = path[childCity].first;
            parentIndex = path[childCity].second;
            }



        }

        childCity = destination;
        parentCity = path[childCity].first;
        parentIndex = path[childCity].second;

        while(childCity != source) {
            updatedGraph[parentCity].at(parentIndex).flow += minRemainCap;
            updatedGraph[parentCity].at(parentIndex).remainingCap -= minRemainCap;

            childCity = parentCity;

            if (childCity != source) {
            parentCity = path[childCity].first;
            parentIndex = path[childCity].second;
            }

        }

        originalGraph = updatedGraph;

        pathFlow = minRemainCap;


        return pathFlow;
    }


    int maxFlow() {
        int maxFlow = 0;
        //Bool turns false once there are no more paths to dest node
        bool pathPossible = true;

        while (pathPossible) {
            map<string, pair<string, int>> path;
            path = BFS();

            if (path.find(destination) != path.end()) {
                maxFlow = maxFlow + UpdateGraph(path);
            }
            else {
                pathPossible = false;
            }
        }
        return maxFlow;
    }


    void PrintGraph() {
        for (auto it = originalGraph.begin(); it != originalGraph.end(); it++) {
            cout << it->first << ": ";
            for (int i = 0; i < it->second.size(); i++) {
                cout << it->second.at(i).to << ", flow: " << it->second.at(i).flow;
                cout << ", remaining capacity: " <<it->second.at(i).remainingCap << endl;
            }
        }
    }

    void PrintBFS() {
        map<string,pair<string, int>> path = BFS();

        for (auto it = path.begin(); it != path.end(); it++) {
            cout << "Child: " << it->first << " Parent: " << it->second.first;
            cout << " Index: " << it->second.second << endl;
        }
    }

};
