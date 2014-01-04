#include "suffix-tree.h"

/* Konstruktor domyœlny - tworzy korzeñ o indeksach -1,-1
 * @author: Tomasz Szo³tysek
 */
suffixTree::suffixTree() 
{
	root = make_shared<edge>(edge(-1,-1));
}

/* Konstruktor w oparciu o s³owo
 * @param s: s³owo, dla którego ma byæ utworzone drzewo sufiksów
 * @author: Tomasz Szo³tysek
 */
suffixTree::suffixTree(string s) 
{
	root = make_shared<edge>(edge(-1,-1));	// inicjalizacja korzenia

	sequence = s;	// zapisanie s³owa
	edgeptr tmp,tmp1;	// zmienna tymczasowa - wskaŸnik na krawêdŸ

	// pêtla wstawiaj¹ca sufiksy w kolejnoœci od najd³u¿szego do najkrótszego
	for(unsigned int i=0; i< s.length(); ++i)
	{
		string subs = s.substr(i,string::npos);	// "wycinanie" treœci sufiksu ze s³owa

		tmp = root;
		int offset,l;
		// sprawdzenie, czy od korzenia odchodzi ju¿ sufiks na tê literê
		if(findEdge(s[i],tmp))
		{
			offset = 0;	// zmienna pomocnicza - stosowana dla przejœæ miêdzy krawêdziami przy wyszukiwaniu d³ugoœci czêœci wspólnej
			l = commonSize(subs,tmp,offset); // jak d³uga jest czêœæ wspólna sufiksów

			// podzia³ sufiksu na czêœæ wspóln¹ i resztê
			// tmp = czêœæ górna przy podziale, bottomEdge = czêœæ dolna
			edgeptr bottomEdge = make_shared<edge>(edge(tmp->getStart()+l,tmp->getEnd()));
			tmp->setEnd(tmp->getStart()+l);

			// po³¹czenie czêœci krawêdzi sufiksu
			bottomEdge->childNode = tmp->childNode;
			tmp->childNode = bottomEdge;

			// dodanie reszty nowego sufiksu
			tmp = make_shared<edge>(edge(i+l+offset,s.length()));
			bottomEdge->rightNode = tmp;
		}
		else 
		{
			if(root->childNode != nullptr)	// wstawianie niepustego drzewa
			{
				tmp = root->childNode;
				tmp1 = tmp->rightNode;
				while (tmp1 != nullptr)	// przejœcie przez wszystkich "braci" krawêdzi na pierwszym poziomie
				{
					tmp = tmp1;
					tmp1 = tmp->rightNode;
				}
				tmp->rightNode = make_shared<edge>(edge(i,s.length()));	// wstawienie krawêdzi
				tmp = tmp->rightNode;
			}
			else	// wstawianie do pustego drzewa
			{
				tmp = make_shared<edge>(edge(i,s.length()));
				root->childNode = tmp;
			}
		}
		if(tmp->childNode == nullptr)
			tmp->childNode = make_shared<edge>(edge(INT_MAX,INT_MAX));	// oznaczenie koñca sufiksu
	}
}

/* Destruktor domyœlny
 * @author: Tomasz Szo³tysek
 */
suffixTree::~suffixTree() 
{
}

/* Wyszukiwanie krawêdzi, która zaczyna siê na znak c
 * @param c: znak, dla którego ma byæ znaleziona krawêdŸ
 * @param e: wskaŸnik od której ma byæ rozpoczête wyszukiwanie (i przez który krawêdŸ zostanie zwrócona)
 * @return: true jeœli znaleziono krawêdŸ zaczynaj¹c¹ siê na znak c, w innym razie false
 * @author: Tomasz Szo³tysek
 */
bool suffixTree::findEdge(char c, edgeptr &e)
{
	edgeptr tmp = e->childNode;
	
	while(tmp != nullptr)	// pêtla po rodzenstwie krawêdzi e
	{
		if(sequence[tmp->getStart()] == c)
		{	// porównanie znaku c z pierwszym znakiem krawêdzi tmp
			e = tmp;
			return true;
		} 
		else
			tmp = tmp->rightNode;
	}
	return false;
}

/* Sprawdzenie d³ugoœci czêœci wspólnej aktualnie wstawianego sufiksu i krawêdzi (wraz z potomstwem) [rekurencyjna]
 * @param s: aktualnie wstawiany sufiks
 * @param e: krawêdŸ z któr¹ bêdzie porównywany sufiks (w razie przejœæ modyfikowana na aktualnie badan¹ krawêdŸ)
 * @param o: offset stosowany w razie przejœæ na potomstwo krawêdzi - zawiera sumê d³ugoœci krawêdzi przodków
 * @return: d³ugoœæ czêœci wspólnej ostatniego potomstwa i sufiksu skróconej od góry o offset
 */
int suffixTree::commonSize(string s, edgeptr& e, int& o)
{
	int si, ei;	// indeksy pocz¹tku i koñca krawêdzi
	si = e->getStart();
	ei = e->getEnd();
	string subm = sequence.substr(si,ei - si);	// wyciêcie tekstu krawêdzi z ci¹gu znaków drzewa
	unsigned int x = s.size() > subm.size() ? subm.size() : s.size();	// sprawdzenie co jest d³u¿sze - krawêdŸ e czy sufiks s
	unsigned int i = 0;
	for(i=0; i < x; ++i)	// pêtla po znakach krawêdzi i sufiksu
	{
		if(s[i] != subm[i])	// jeœli znaki siê ró¿ni¹, to zwróæ iloœæ przebadanych znaków jako rezultat
			return i;
	}
	if(findEdge(s[i],e))	// jeœli ca³a krawêdŸ siê zgadza, to sprawdŸ, czy potomek nie zaczyna siê na zgodny znak
	{
		o += i;	// jeœli tak, to zwiêksz offset o d³ugoœæ krawêdzi badanej w tej metodzie
		return commonSize(s.substr(i,string::npos),e,o);	// i sprawdŸ ile znaków zgadza siê w reszcie sufiksu i s³owie
	}
	return i;
}

/* Metoda zwracaj¹ca pocz¹tek drzewa sufiksów
 * @return: wektor wskaŸników na krawêdzie pierwszego sufiksu w drzewie
 * @author: Tomasz Szo³tysek
 */
vector<edgeptr> suffixTree::begin()
{
	vector<edgeptr> p;
	edgeptr x = root;
	while(x->childNode != nullptr)
	{
		x = x->childNode;
		p.push_back(x);
	}
	return p;
}

/* Metoda zwracaj¹ca warunek stopu
 * @return: pusty wektor wskaŸników na krawêdzie
 * @author: Tomasz Szo³tysek
 */
vector<edgeptr> suffixTree::end()
{
	return vector<edgeptr>();
}

/* Metoda zwracaj¹ca ostatni sufiks drzewa
 * @return: wektor wskaŸników na krawêdzie ostatniego sufiksu w drzewie
 * @author: Tomasz Szo³tysek
 */
vector<edgeptr> suffixTree::back()
{
	vector<edgeptr> p;
	edgeptr x = root;
	while(x->childNode != nullptr)
	{
		x = x->childNode;
		while(x->rightNode != nullptr)
			x = x->rightNode;
		p.push_back(x);
	}
	return p;
}

/* Konstruktor iteratora w oparciu o wskaŸnik na krawêdŸ
 * @param x: wskaŸnik na krawêdŸ od której zaczyna siê sufiks
 * @author: Tomasz Szo³tysek
 */
suffixTree::myIterator::myIterator(edgeptr &x)
{
	edgeptr& y = x;
	p.push_back(x);
	while(y->childNode != nullptr)
	{
		y = y->childNode;
		p.push_back(y);
	}
}

/* Konstruktor iteratora w oparciu o wektor wskaŸników na krawêdzie sufiksu
 * @param x: wektor wskaŸników na krawêdzie sufiksu
 * @author: Tomasz Szo³tysek
 */
suffixTree::myIterator::myIterator(vector<edgeptr> &x)
{
	p = x;
}

/* Konstruktor iteratora w oparciu o drzewo sufiksów
 * @param x: drzewo sufiksów
 * @author: Tomasz Szo³tysek
 */
suffixTree::myIterator::myIterator(suffixTree &x)
{
	edgeptr& y = x.getFirst();
	p.push_back(y);
	while(y->childNode != nullptr)
	{
		y = y->childNode;
		p.push_back(y);
	}
}

/* operator przypisania wektora wskaŸników na krawêdzie sufiksu
 * @param x: wektor wskaŸników na krawêdzie sufiksu
 * @author: Tomasz Szo³tysek
 */
void suffixTree::myIterator::operator=(vector<edgeptr> &x) 
{
	p = x;
}

/* operator przypisania innego iteratora
 * @param x: iterator, którego wartoœæ ma byæ przypisana
 * @author: Tomasz Szo³tysek
 */
void suffixTree::myIterator::operator=(myIterator &x) 
{
	vector<edgeptr> q = x.get();
	p.swap(p);
}

/* getter
 * @return: wektor wskaŸników na krawêdzie sufiksu, na który aktualnie wskazuje iterator
 * @author: Tomasz Szo³tysek
 */
const vector<edgeptr> suffixTree::myIterator::get()
{
	return p;
}

/* operator porównania z innym iteratorem
 * @param x: iterator do porównania
 * @return: true, jeœli iteratory wskazuj¹ na to samo, inaczej false
 * @author: Tomasz Szo³tysek
 */
bool suffixTree::myIterator::operator==(myIterator &x)
{
	vector<edgeptr> q = x.get();
	vector<edgeptr>::iterator p_it = p.begin();
	vector<edgeptr>::iterator q_it = q.begin();
	while (p_it != p.end() && q_it != q.end()) 
	{
		if (*p_it != *q_it) 
			return false;
		p_it++;
		q_it++;
	}
	
	// Account for different length vector instances
	if (p_it != p.end() || q_it != q.end())
		return false;
	
	return true;
}

/* operator porównania z wektorem wskaŸników na krawêdzie sufiksu
 * @param x: wektor krawêdzi do porównania
 * @return: true, jeœli iterator zawiera taki sam wektor jak parametr x, inaczej false
 * @author: Tomasz Szo³tysek
 */
bool suffixTree::myIterator::operator==(vector<edgeptr> &x)
{
	vector<edgeptr>::iterator p_it = p.begin();
	vector<edgeptr>::iterator q_it = x.begin();
	while (p_it != p.end() && q_it != x.end()) 
	{
		if (*p_it != *q_it) 
			return false;
		p_it++;
		q_it++;
	}
	
	// Account for different length vector instances
	if (p_it != p.end() || q_it != x.end())
		return false;
	
	return true;
}

/* Wyszukiwanie nastêpnika elementu iteratora
 * @return: wskaŸnik na nastêpnik elementu
 * @author: Tomasz Szo³tysek
 */
const vector<edgeptr> suffixTree::myIterator::next() 
{
	if(p.empty())
		return vector<edgeptr>();
	edgeptr x = p.back();
	p.pop_back();
	if(x->rightNode != nullptr)
	{
		x = x->rightNode;
		p.push_back(x);
		while(x->childNode != nullptr)
		{
			x = x->childNode;
			p.push_back(x);
		}
		return p;
	}
	else return next();
}

/* Operator preinkrementacji - wykonuje to samo co next(), tylko bez zwracania wartoœci
 * @author: Tomasz Szo³tysek
 */
void suffixTree::myIterator::operator++()
{
	next();
}

/* Operator postinkrementacji - wykonuje to samo co next(), tylko bez zwracania wartoœci
 * @author: Tomasz Szo³tysek
 */
void suffixTree::myIterator::operator++(int a)
{
	next();
}