#include "Graph1.h"
#include <iostream>;
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
	return true;
}

bool Graph::rem_vert(char label) {
	Vertex *delVert = 0, *prevVert = 0;
	for (Vertex *tempVert = this->vertList; tempVert; tempVert = tempVert->next) {
		if (tempVert->label !=label) {
			for (Edge *tempEdge = tempVert->edgeList; tempEdge; tempEdge = tempEdge->next) {
				if (tempEdge->to->label == label) {
					return false;
				}
			}
			if (tempVert->next && tempVert->next->label == label) {
				prevVert = tempVert;
			}
		}
		else {
			delVert = tempVert;
		}
	}
	if (delVert) {
		if (prevVert) {
			prevVert->next = delVert->next;
		}
		else {
			this->vertList = delVert->next;
		}
		delete delVert;
		return true;
	}
	else {
		return false;
	}
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

void Graph::visitNeighbors(){
	for (Edge *temp = this->vertList->edgeList; temp->edgeList; temp = temp->next){
		cout << temp << endl;
	}
}


/* def gtrav(6,3)
push 5 onto stack
while stack not empty
	pop stack into v
if v unvisited{ mark v visited
	push all v's adjacent vertices}

	Stack 5 2 7 6 10
	Visited: 5 7 10 6 3 4 1
	
	      5
	   3     7
	1    4  6   10
	
	Queue
	Visited: 5 3 7 1 4 6 10*/
