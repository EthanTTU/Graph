#include "Graph1.h"
#include <iostream>
using namespace std;

int main() {
	Graph x;
	x.add_vert('A');
	x.add_vert('B');
	x.add_vert('C');
	x.add_vert('D');
	
	//x.visit();
	x.add_edge('A', 'B', 8);
	x.add_edge('A', 'C', 22);
	x.add_edge('B', 'C', 7);
	x.add_edge('B', 'D', 15);
	x.add_edge('D', 'C', 18);
	x.visitNeighbors();
	
	//x.add_edge(0, 2);
	//x.add_edge(1, 2);
	//x.add_edge(2, 0);
	//x.add_edge(2, 3);
	//x.add_edge(3, 3);
	x.display();
	system("pause");
	return 0;
}