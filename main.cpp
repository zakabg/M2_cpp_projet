#include "gate.h"
#include "graph.h"
#include <vector>
#include <iostream> 
#include <fstream>  
#include <sstream>  

using namespace std;

int main(){
	GRAPH g;
	g.parseFile();  
	g.solve();    
	return 0;
}
