#include "edge.h"

edge::edge() 
{
	this->startIndex = -1;
	this->endIndex = -1;
	this->childNode = nullptr;
	this->rightNode = nullptr;
}

edge::edge(int start, int end) 
{
	this->startIndex = start;
	this->endIndex = end;
	this->childNode = nullptr;
	this->rightNode = nullptr;
}

edge::edge(int start, int end, shared_ptr<edge> child, shared_ptr<edge> right) 
{
	this->startIndex = start;
	this->endIndex = end;
	this->childNode = child;
	this->rightNode = right;
}

int edge::getStart()
{
	return startIndex;
}

int edge::getEnd()
{
	return endIndex;
}

void edge::setStart(int s) 
{
	startIndex = s;
}
void edge::setEnd(int e)
{
	endIndex = e;
}

int edge::commonSize(string s, string m)
{
	string subm = m.substr(startIndex,endIndex - startIndex);
	int x = s.size() > subm.size() ? subm.size() : s.size();
	for(unsigned int i=0; i < x; ++i)
	{
		if(s[i] != subm[i])
			return i;
	}
	return 0;
}

edge::~edge() {}