#include "edge.h"

/* Konstruktor domyœlny
 * @author: Tomasz Szo³tysek
 */
edge::edge() 
{
	this->startIndex = -1;
	this->endIndex = -1;
	this->childNode = nullptr;
	this->rightNode = nullptr;
}

/* Konstruktor w oparciu o parê indeksów
 * @param start: indeks pierwszego znaku w krawêdzi
 * @param end: indeks ostatniego+1 znaku w krawêdzi
 * @author: Tomasz Szo³tysek
 */
edge::edge(int start, int end) 
{
	this->startIndex = start;
	this->endIndex = end;
	this->childNode = nullptr;
	this->rightNode = nullptr;
}

/* Konstruktor z zadanymi potomkiem i rodzeñstwem
 * @param start: indeks pierwszego znaku w krawêdzi
 * @param end: indeks ostatniego+1 znaku w krawêdzi
 * @param child: wskaŸnik na potomka
 * @param right: wskaŸnik na rodzeñstwo
 * @author: Tomasz Szo³tysek
 */
edge::edge(int start, int end, shared_ptr<edge> child, shared_ptr<edge> right) 
{
	this->startIndex = start;
	this->endIndex = end;
	this->childNode = child;
	this->rightNode = right;
}

/* Getter indeksu pierwszego znaku krawêdzi
 * @return: indeks pierwszego znaku krawêdzi
 * @author: Tomasz Szo³tysek
 */
int edge::getStart()
{
	return startIndex;
}

/* Getter indeksu ostatniego+1 znaku krawêdzi
 * @return: indeks ostatniego+1 znaku krawêdzi
 * @author: Tomasz Szo³tysek
 */
int edge::getEnd()
{
	return endIndex;
}


/* Setter indeksu pierwszego znaku krawêdzi
 * @param s: indeks pierwszego znaku krawêdzi
 * @author: Tomasz Szo³tysek
 */
void edge::setStart(int s) 
{
	startIndex = s;
}

/* Setter indeksu ostatniego+1 znaku krawêdzi
 * @param e: indeks ostatniego+1 znaku krawêdzi
 * @author: Tomasz Szo³tysek
 */
void edge::setEnd(int e)
{
	endIndex = e;
}

/* Destruktor domyœlny
 * @author: Tomasz Szo³tysek
 */
edge::~edge() 
{
}