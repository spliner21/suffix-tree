#include "edge.h"

/* Konstruktor domy�lny
 * @author: Tomasz Szo�tysek
 */
edge::edge() 
{
	this->startIndex = -1;
	this->endIndex = -1;
	this->childNode = nullptr;
	this->rightNode = nullptr;
}

/* Konstruktor w oparciu o par� indeks�w
 * @param start: indeks pierwszego znaku w kraw�dzi
 * @param end: indeks ostatniego+1 znaku w kraw�dzi
 * @author: Tomasz Szo�tysek
 */
edge::edge(int start, int end) 
{
	this->startIndex = start;
	this->endIndex = end;
	this->childNode = nullptr;
	this->rightNode = nullptr;
}

/* Konstruktor z zadanymi potomkiem i rodze�stwem
 * @param start: indeks pierwszego znaku w kraw�dzi
 * @param end: indeks ostatniego+1 znaku w kraw�dzi
 * @param child: wska�nik na potomka
 * @param right: wska�nik na rodze�stwo
 * @author: Tomasz Szo�tysek
 */
edge::edge(int start, int end, shared_ptr<edge> child, shared_ptr<edge> right) 
{
	this->startIndex = start;
	this->endIndex = end;
	this->childNode = child;
	this->rightNode = right;
}

/* Getter indeksu pierwszego znaku kraw�dzi
 * @return: indeks pierwszego znaku kraw�dzi
 * @author: Tomasz Szo�tysek
 */
int edge::getStart()
{
	return startIndex;
}

/* Getter indeksu ostatniego+1 znaku kraw�dzi
 * @return: indeks ostatniego+1 znaku kraw�dzi
 * @author: Tomasz Szo�tysek
 */
int edge::getEnd()
{
	return endIndex;
}


/* Setter indeksu pierwszego znaku kraw�dzi
 * @param s: indeks pierwszego znaku kraw�dzi
 * @author: Tomasz Szo�tysek
 */
void edge::setStart(int s) 
{
	startIndex = s;
}

/* Setter indeksu ostatniego+1 znaku kraw�dzi
 * @param e: indeks ostatniego+1 znaku kraw�dzi
 * @author: Tomasz Szo�tysek
 */
void edge::setEnd(int e)
{
	endIndex = e;
}

/* Destruktor domy�lny
 * @author: Tomasz Szo�tysek
 */
edge::~edge() 
{
}