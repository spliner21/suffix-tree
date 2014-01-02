#pragma once 

#include <iostream>
#include <memory>

using namespace std;

/* KrawêdŸ w drzewie
 * przechowuje indeks pierwszego i ostatniego znaku w odnodze drzewa
 * @autor: Tomasz Szo³tysek
 */
class edge 
{
private:
	int startIndex;	// indeks pierwszego znaku krawêdzi
	int endIndex;	// indeks ostatniego znaku krawêdzi
	
public:
	shared_ptr<edge> childNode; // left-most child
	shared_ptr<edge> rightNode;	// right sibling
	
	edge();
	edge(int start, int end);
	edge(int start, int end, shared_ptr<edge> child, shared_ptr<edge> right);
	~edge();
	
	int getStart();
	int getEnd();
	void setStart(int s);
	void setEnd(int e);

	int commonSize(string s, string m);
};