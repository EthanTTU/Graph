#include "Graph1.h"
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
	for(; current->label == source; current = current->next) {}

	// Mark the source as visited and put it in the other maps
	this->mapHeap[source] = 0;
	current->visited = true;
	this->pathMap[source] = NULL;
	this->distanceMap[source] = 0;

	while (!mapHeap.empty()) {
		current = findSmallestUnvisitedVertexInMap();
		visitNeighbors(current);
	}

	// Print out the maps here
}

void Graph::visitNeighbors(Vertex *current){
	// Goes through all of the nayboring edges
	for (Edge* temp = current->edgeList; temp; temp = temp->next){
		// If the mapHeap has a value greater than the edge we are looking at
		if (this->mapHeap[temp->to->label] > temp->weight) {
			this->mapHeap[temp->to->label] = temp->weight;
			this->pathMap[temp->to->label] = current->label;
		}
		// Otherwise...
		else {

		}
	}
}

bool Graph::isVisited(char label) {
	Vertex *current = this->vertList;
	for (; current->label == label; current = current->next) {}

	return current->visited;
}

char Graph::findSmallestUnvisitedVertexInMap() {
	char minLabel;
	int minValue = INT_MAX;
	for (map<char, int>::iterator it = this->mapHeap.begin(); it != this->mapHeap.end(); ++it) {
		if ((it->second < minValue) && (!isVisited(it->first))) {
			minValue = it->second;
			minLabel = it->first;
		}
	}

	return minLabel;
}

char Graph::checkState() {
  cout << "Distance Map: " << endl;
  for (map<char,int>::iterator it=this->distanceMap.begin(); it!=this->distanceMap.end(); ++it)
    cout << it->first << " => " << it->second << '\n';

  cout << "Path Map: " << endl;
  for (map<char,char>::iterator it=this->pathMap.begin(); it!=this->pathMap.end(); ++it)
    cout << it->first << " => " << it->second << '\n';
}
