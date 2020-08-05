#include "Graph.h"

bool Graph::Exists(string key) {
	if ((graph->size() != 0) && (graph->find(key) != graph->end()))
		return true;
	return false;
}

void Graph::InsertEdge(string from, string to, int weight) {
	(*graph)[from][to] = weight;
	if (graph->find(to) == graph->end())
		(*graph)[to] = {};
}

bool Graph::IsEdge(string from, string to) {
	auto iter = graph->find(from);
	if (iter != graph->end())
		if (iter->second.find(to) != iter->second.end())
			return true;
	return false;
}

void Graph::PrintGraph() {
	for (auto iter = graph->begin(); iter != graph->end(); iter++) {
		cout << iter->first;
		for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
			cout << "," << iter2->first << "," << iter2->second;
		cout << endl;
	}
}