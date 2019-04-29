#include "GraphProject.h"
#include <iostream>
#include <climits>

using namespace std;

void Graph::destr_helper(Vertex* vert) {
	if (vert) {
		this->destr_helper(vert->next);
		delete vert;
	}
}

Graph::~Graph() {
	this->destr_helper(this->vertList);
}

bool Graph::add_vert(char label) {
	for (Vertex *tempVert = this->vertList; tempVert; tempVert = tempVert->next) {
		if (tempVert->label == label) {
			return false;
		}
	}
	Vertex *newNode = new Vertex(label);
	newNode->next = this->vertList;
	this->vertList = newNode;
	this->mapHeap[label] = INT_MAX;
	return true;
}

bool Graph::add_edge(char from, char to, int weight) {
	Vertex *tempVert, *fromVert = 0, *toVert = 0;

	// Finds target nodes
	for (tempVert = this->vertList; tempVert; tempVert = tempVert->next) { //goes through all verticies
		if (tempVert->label == from) {
			fromVert = tempVert;
		}
		if (tempVert->label == to) {
			toVert = tempVert;
		}
	}

	// Error handling
	if (!fromVert || !toVert) {
		return false;
	}

	// Creates new Edge and it to the edge list
	Edge *newEdge = new Edge(toVert);
	newEdge->next = fromVert->edgeList;
	newEdge->weight = weight;
	fromVert->edgeList = newEdge;
	return true;
}

void Graph::visit(Vertex *vert) {
	if (vert) {
		this->visit(vert->next);
		cout << vert->label << endl;
	}
}

void Graph::display() {
	for(Vertex *vert = this->vertList; vert; vert = vert->next) {
		cout << getLabel(vert->label) << " -> ";
		if (vert->edgeList) {
			cout << vert->edgeList->to->label;
			for (Edge *edge = vert->edgeList->next; edge; edge = edge->next) {
				cout << ", " << getLabel(edge->to->label);
			}
		}
		cout << endl;
	}
}

char Graph::getLabel(char label) {
	int a = label;
	return label;
}

void Graph::djikstras(char source) {
	Vertex *current = vertList;
	for(; current->label != source; current = current->next) {}

	cout << "Ruuning Djikstra's for " <<current->label << endl;
	// Mark the source as visited and put it in the other maps
	this->mapHeap[source] = 0;
	this->pathMap[source] = 'N';
	this->distanceMap[source] = 0;

	
	while (!mapHeap.empty()) {
		
		// Save the current's distance from source into the distance map
		this->distanceMap[current->label] = this->mapHeap[current->label];
		// Visit all of the neighbors
		visitNeighbors(current);
		
		// Mark the current node as visited
		this->mapHeap.erase(current->label);
		
		// Find a new current, which is the smallest distance in the map
		char minLabel;
		Vertex* minVert = this->vertList;
		int minValue = INT_MAX;
		for (map<char, int>::iterator it = this->mapHeap.begin(); it != this->mapHeap.end(); ++it) {
			if (it->second < minValue) {
				minValue = it->second;
				minLabel = it->first;
			}
		}
		
		for (; minVert->label != minLabel; minVert = minVert->next) {}
		
		current = minVert;
	}
	checkState();
}

void Graph::visitNeighbors(Vertex *current){
	// Goes through all of the nayboring edges
	for (Edge* temp = current->edgeList; temp; temp = temp->next){
		
		// If the node is already visited, skip it
		if (this->mapHeap.count(current->label) == 0) {
			continue;
		}
		
		// If the target node has already been visited
		if (this->mapHeap.count(temp->to->label) == 1) {
			int tempMin = temp->weight + this->distanceMap[current->label];
			if (tempMin < this->mapHeap[temp->to->label]) {
				this->mapHeap[temp->to->label] = tempMin;
				this->pathMap[temp->to->label] = current->label;
			}
		}
	}
}

void Graph::checkState() {
	cout << "Distance Map: " << endl;
	for (map<char,int>::iterator it=this->distanceMap.begin(); it!=this->distanceMap.end(); ++it)
		cout << it->first << " => " << it->second << endl;

	cout << "Path Map: " << endl;
	for (map<char,char>::iterator it=this->pathMap.begin(); it!=this->pathMap.end(); ++it)
		cout << it->first << "-" << it->second << endl;
	
	cout << endl;
}
