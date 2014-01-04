#pragma once 

#include <iostream>
#include <string>
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
	int endIndex;	// indeks ostatniego+1 znaku krawêdzi
	
public:
	shared_ptr<edge> childNode; // left-most child
	shared_ptr<edge> rightNode;	// right sibling
	
	edge();	// konstruktor domyœlny
	edge(int start, int end);	// konstruktor w oparciu o indeksy pocz¹tku i koñca krawêdzi
	edge(int start, int end, shared_ptr<edge> child, shared_ptr<edge> right);	// konstruktor otrzymuj¹cy potomka i prawego brata
	~edge();	// destruktor domyœlny
	
	int getStart();	// getter dla indeksu pierwszego znaku
	int getEnd();	// getter dla indeksu ostatniego+1 znaku
	void setStart(int s);	// setter dla indeksu pierwszego znaku
	void setEnd(int e);		// setter dla indeksu ostatniego+1 znaku

	void draw(string s)	// metoda do testu - wyœwietlanie tekstu krawêdzi
	{
		if(startIndex != INT_MAX)
			cout << s.substr(startIndex, endIndex-startIndex);
	}
};