#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
using namespace std;

//Implements a directed, weighted graph as an Adjacency List
class Graph {
private:
	map<int, vector<pair<int, int>>> graph;

public:
	void insertEdge(int from, int to, int weight) {
		graph[from].push_back(make_pair(to, weight));
		if (graph.find(to) == graph.end())
			graph[to] = {};
	};
	bool isEdge(int from, int to) {
		auto iter = graph.find(from);
		if (iter != graph.end()) {
			vector<pair<int, int>> vertices = iter->second;
			for (int vertex = 0; vertex < vertices.size(); vertex++)
				if (vertices[vertex].first == to)
					return true;
		}
		return false;
	};
	int getWeight(int from, int to) {
		auto iter = graph.find(from);
		if (iter != graph.end()) {
			vector<pair<int, int>> vertices = iter->second;
			for (int vertex = 0; vertex < vertices.size(); vertex++)
				if (vertices[vertex].first == to)
					return vertices[vertex].second;
		}
	};
	vector<int> getAdjacent(int from) {
		vector<int> adj;
		auto iter = graph.find(from);
		if (iter != graph.end()) {
			vector<pair<int, int>> vertices = iter->second;
			for (int vertex = 0; vertex < vertices.size(); vertex++)
				adj.push_back(vertices[vertex].first);
		}
		return adj;
	};
	void printGraph() {
		for (auto iter = graph.begin(); iter != graph.end(); iter++) {
			cout << iter->first;
			vector<pair<int, int>> vertices = iter->second;
			for (int vertex = 0; vertex < vertices.size(); vertex++)
				cout << " " << vertices[vertex].first;
			cout << endl;
		}
	};
};