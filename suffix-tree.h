#pragma once

#include "edge.h"
#include <vector>

typedef shared_ptr<edge> edgeptr;

class suffixTree 
{
private:	
	edgeptr root;
	string sequence;
public:
	suffixTree();
	suffixTree(string sequence);
	~suffixTree();

	bool findEdge(char c, edgeptr &e);
};