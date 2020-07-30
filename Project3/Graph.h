#pragma once
#include<iostream>
#include<map>
#include<set>
#include<sstream>
#include<string>
#include<vector>
using namespace std;

//Implements a directed, weighted graph as an Adjacency List
class Graph {
private:
	//map<int, vector<pair<int, int>>> graph;
	map<string, map<string, int>>* graph;

public:
	//Constructor
	Graph() {
		this->graph = new map<string, map<string, int>>;
	}

	//Mutators
	map<string, map<string, int>>::iterator Find(string key) {	return graph->find(key); }
	map<string, map<string, int>>::iterator Begin() { return graph->begin(); }
	map<string, map<string, int>>::iterator End() { return graph->end(); }
	bool Exists(string key) {
		if ((graph->size() != 0) && (graph->find(key) != graph->end()))
			return true;
		return false;
	}
	void InsertEdge(string from, string to, int weight) {
		(*graph)[from][to] = weight;
		if (graph->find(to) == graph->end())
			(*graph)[to] = {};
	}
	bool IsEdge(string from, string to) {
		auto iter = graph->find(from);
		if (iter != graph->end()) 
			if (iter->second.find(to) != iter->second.end())
				return true;
		return false;
	}


	//Accessors
	int GetSize() { return graph->size(); }
	int GetWeight(string from, string to) {	return graph->find(from)->second[to]; };
	set<string> getAdjacent(string from) {
		set<string> adj;
		for (auto iter = graph->begin(); iter != graph->end(); iter++)
			for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
				adj.insert(iter2->first);
		return adj;
	}
	
	//Output
	void PrintGraph() {
		for (auto iter = graph->begin(); iter != graph->end(); iter++) {
			cout << iter->first;
			for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
				cout << "," << iter2->first << "," << iter2->second;
			cout << endl;
		}
	}
};