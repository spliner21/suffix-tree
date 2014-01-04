#pragma once 

#include <iostream>
#include <string>
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
	int endIndex;	// indeks ostatniego+1 znaku kraw�dzi
	
public:
	shared_ptr<edge> childNode; // left-most child
	shared_ptr<edge> rightNode;	// right sibling
	
	edge();	// konstruktor domy�lny
	edge(int start, int end);	// konstruktor w oparciu o indeksy pocz�tku i ko�ca kraw�dzi
	edge(int start, int end, shared_ptr<edge> child, shared_ptr<edge> right);	// konstruktor otrzymuj�cy potomka i prawego brata
	~edge();	// destruktor domy�lny
	
	int getStart();	// getter dla indeksu pierwszego znaku
	int getEnd();	// getter dla indeksu ostatniego+1 znaku
	void setStart(int s);	// setter dla indeksu pierwszego znaku
	void setEnd(int e);		// setter dla indeksu ostatniego+1 znaku

	void draw(string s)	// metoda do testu - wy�wietlanie tekstu kraw�dzi
	{
		if(startIndex != INT_MAX)
			cout << s.substr(startIndex, endIndex-startIndex);
	}
};