#pragma once
#include<iostream>
#include<map>
#include<set>
#include<string>
#include<vector>
using namespace std;

//Implements a directed, weighted graph as an Adjacency List
class Graph {
	map<string, map<string, int> >* graph;

public:
	//Constructor
	Graph() {
		this->graph = new map<string, map<string, int> >;
	}

	//Mutators
	map<string, map<string, int> >::iterator Find(string key) {	return graph->find(key); }
	map<string, map<string, int> >::iterator Begin() { return graph->begin(); }
	map<string, map<string, int> >::iterator End() { return graph->end(); }
	bool Exists(string key);
	void InsertEdge(string from, string to, int weight);
	bool IsEdge(string from, string to);

	//Accessors
	int GetSize() { return graph->size(); }
	int GetWeight(string from, string to) {	return graph->find(from)->second[to]; };

	//Output
	void PrintGraph();
};
