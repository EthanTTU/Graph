#include "GraphProject.h"
#include <iostream>
using namespace std;

int main() {
	Graph x;
	x.source = 'A';
	x.add_vert('D');
	x.add_vert('C');
	x.add_vert('B');
	x.add_vert('A');
	
	x.add_edge('A', 'B', 8);
	x.add_edge('B', 'A', 8);
	x.add_edge('A', 'C', 22);
	x.add_edge('C', 'A', 22);
	x.add_edge('B', 'C', 7);
	x.add_edge('C', 'B', 7);
	x.add_edge('B', 'D', 15);
	x.add_edge('D', 'B', 15);
	x.add_edge('D', 'C', 18);
	x.add_edge('C', 'D', 18);
	
	x.djikstras('B');
	system("pause");
	return 0;
}