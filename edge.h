#pragma once 

#include <iostream>
#include <memory>

using namespace std;

/* Kraw�d� w drzewie
 * przechowuje indeks pierwszego i ostatniego znaku w odnodze drzewa
 * @autor: Tomasz Szo�tysek
 */
class edge 
{
private:
	int startIndex;	// indeks pierwszego znaku kraw�dzi
	int endIndex;	// indeks ostatniego znaku kraw�dzi
	
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