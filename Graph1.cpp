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

bool Graph::add_edge(char from, char to, int distance) {
	Vertex *tempVert, *fromVert = 0, *toVert = 0;
	for (tempVert = this->vertList; tempVert; tempVert = tempVert->next) { //goes through all verticies
		if (tempVert->label == from) {
			fromVert = tempVert;
		}
		if (tempVert->label == to) {
			toVert = tempVert;
		}
	}
	if (!fromVert || !toVert) {
		return false;
	}
	Edge *newEdge = new Edge(toVert);
	newEdge->next = fromVert->edgeList;
	newEdge->weight = distance;
	fromVert->edgeList = newEdge;
	return true;
}
bool Graph::rem_edge(char from, char to) {
	Vertex *Vert;
	Edge *edge, *prev = 0;
	for (Vert = this->vertList; Vert; Vert->next) {
		if (Vert->label == from) {
			break;
		}
	}
	if (!Vert) {
		return false;
	}
	for (edge = Vert->edgeList; edge; edge = edge->next) {
		if (edge->next && edge->next->to->label == to) { //checks for next pointer first
			prev = edge;
		}
		if (edge->to->label == to) {
			break;
		}
	}

	if (edge) {
		if (!prev) { //if edge is at the head
			Vert->edgeList = edge->next; 
		}
		else {
			prev->next = edge->next;
		}
		delete edge;
		return true;
	}
	else {
		return false;
	}
}

void Graph::DFT(char source) {
	Vertex *temp = this->vertList;
	for (; temp && temp->label != source; temp = temp->next);
	if (temp){
		stack_push(temp);
	}
	else {
		return;
	}
	while (stack) {
		temp = stack; //pop stack
		stack = stack->next; //pop stack
		temp->next = this->visited; //pop stack
		this->visited = temp;
		Edge *eTemp = temp->edgeList;
		for (; eTemp; eTemp = eTemp->next) {
			if (!eTemp->to->visited) {
				stack_push(eTemp->to);
			}
		}
		if (!this->stack && this->vertList) {
			stack_push(this->vertList);
		}
	}
	this->visit(this->visited);
	this->vertList = this->visited;
	this->visited = 0;
	for (temp = this->vertList; temp; temp = temp->next) {
		temp->visited = false;
	}
}

void Graph::stack_push(Vertex *pushNode) {
	Vertex *prev = 0, *temp = vertList;
	pushNode->visited = true;
	for (; temp && temp != pushNode; temp = temp->next) {
		prev = temp;
	}
	if (prev) {
		prev->next = temp->next;
	}
	else {
		this->vertList = this->vertList->next;
	}
	temp->next = stack;
	stack = temp;
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
