#include "suffix-tree.h"

/* Konstruktor domy�lny - tworzy korze� o indeksach -1,-1
 * @author: Tomasz Szo�tysek
 */
suffixTree::suffixTree() 
{
	root = make_shared<edge>(edge(-1,-1));
}

/* Konstruktor w oparciu o s�owo
 * @param s: s�owo, dla kt�rego ma by� utworzone drzewo sufiks�w
 * @author: Tomasz Szo�tysek
 */
suffixTree::suffixTree(string s) 
{
	root = make_shared<edge>(edge(-1,-1));	// inicjalizacja korzenia

	sequence = s;	// zapisanie s�owa
	edgeptr tmp,tmp1;	// zmienna tymczasowa - wska�nik na kraw�d�

	// p�tla wstawiaj�ca sufiksy w kolejno�ci od najd�u�szego do najkr�tszego
	for(unsigned int i=0; i< s.length(); ++i)
	{
		string subs = s.substr(i,string::npos);	// "wycinanie" tre�ci sufiksu ze s�owa

		tmp = root;
		int offset,l;
		// sprawdzenie, czy od korzenia odchodzi ju� sufiks na t� liter�
		if(findEdge(s[i],tmp))
		{
			offset = 0;	// zmienna pomocnicza - stosowana dla przej�� mi�dzy kraw�dziami przy wyszukiwaniu d�ugo�ci cz�ci wsp�lnej
			l = commonSize(subs,tmp,offset); // jak d�uga jest cz�� wsp�lna sufiks�w

			// podzia� sufiksu na cz�� wsp�ln� i reszt�
			// tmp = cz�� g�rna przy podziale, bottomEdge = cz�� dolna
			edgeptr bottomEdge = make_shared<edge>(edge(tmp->getStart()+l,tmp->getEnd()));
			tmp->setEnd(tmp->getStart()+l);

			// po��czenie cz�ci kraw�dzi sufiksu
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
				while (tmp1 != nullptr)	// przej�cie przez wszystkich "braci" kraw�dzi na pierwszym poziomie
				{
					tmp = tmp1;
					tmp1 = tmp->rightNode;
				}
				tmp->rightNode = make_shared<edge>(edge(i,s.length()));	// wstawienie kraw�dzi
				tmp = tmp->rightNode;
			}
			else	// wstawianie do pustego drzewa
			{
				tmp = make_shared<edge>(edge(i,s.length()));
				root->childNode = tmp;
			}
		}
		if(tmp->childNode == nullptr)
			tmp->childNode = make_shared<edge>(edge(INT_MAX,INT_MAX));	// oznaczenie ko�ca sufiksu
	}
}

/* Destruktor domy�lny
 * @author: Tomasz Szo�tysek
 */
suffixTree::~suffixTree() 
{
}

/* Wyszukiwanie kraw�dzi, kt�ra zaczyna si� na znak c
 * @param c: znak, dla kt�rego ma by� znaleziona kraw�d�
 * @param e: wska�nik od kt�rej ma by� rozpocz�te wyszukiwanie (i przez kt�ry kraw�d� zostanie zwr�cona)
 * @return: true je�li znaleziono kraw�d� zaczynaj�c� si� na znak c, w innym razie false
 * @author: Tomasz Szo�tysek
 */
bool suffixTree::findEdge(char c, edgeptr &e)
{
	edgeptr tmp = e->childNode;
	
	while(tmp != nullptr)	// p�tla po rodzenstwie kraw�dzi e
	{
		if(sequence[tmp->getStart()] == c)
		{	// por�wnanie znaku c z pierwszym znakiem kraw�dzi tmp
			e = tmp;
			return true;
		} 
		else
			tmp = tmp->rightNode;
	}
	return false;
}

/* Sprawdzenie d�ugo�ci cz�ci wsp�lnej aktualnie wstawianego sufiksu i kraw�dzi (wraz z potomstwem) [rekurencyjna]
 * @param s: aktualnie wstawiany sufiks
 * @param e: kraw�d� z kt�r� b�dzie por�wnywany sufiks (w razie przej�� modyfikowana na aktualnie badan� kraw�d�)
 * @param o: offset stosowany w razie przej�� na potomstwo kraw�dzi - zawiera sum� d�ugo�ci kraw�dzi przodk�w
 * @return: d�ugo�� cz�ci wsp�lnej ostatniego potomstwa i sufiksu skr�conej od g�ry o offset
 */
int suffixTree::commonSize(string s, edgeptr& e, int& o)
{
	int si, ei;	// indeksy pocz�tku i ko�ca kraw�dzi
	si = e->getStart();
	ei = e->getEnd();
	string subm = sequence.substr(si,ei - si);	// wyci�cie tekstu kraw�dzi z ci�gu znak�w drzewa
	unsigned int x = s.size() > subm.size() ? subm.size() : s.size();	// sprawdzenie co jest d�u�sze - kraw�d� e czy sufiks s
	unsigned int i = 0;
	for(i=0; i < x; ++i)	// p�tla po znakach kraw�dzi i sufiksu
	{
		if(s[i] != subm[i])	// je�li znaki si� r�ni�, to zwr�� ilo�� przebadanych znak�w jako rezultat
			return i;
	}
	if(findEdge(s[i],e))	// je�li ca�a kraw�d� si� zgadza, to sprawd�, czy potomek nie zaczyna si� na zgodny znak
	{
		o += i;	// je�li tak, to zwi�ksz offset o d�ugo�� kraw�dzi badanej w tej metodzie
		return commonSize(s.substr(i,string::npos),e,o);	// i sprawd� ile znak�w zgadza si� w reszcie sufiksu i s�owie
	}
	return i;
}

/* Metoda zwracaj�ca pocz�tek drzewa sufiks�w
 * @return: wektor wska�nik�w na kraw�dzie pierwszego sufiksu w drzewie
 * @author: Tomasz Szo�tysek
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

/* Metoda zwracaj�ca warunek stopu
 * @return: pusty wektor wska�nik�w na kraw�dzie
 * @author: Tomasz Szo�tysek
 */
vector<edgeptr> suffixTree::end()
{
	return vector<edgeptr>();
}

/* Metoda zwracaj�ca ostatni sufiks drzewa
 * @return: wektor wska�nik�w na kraw�dzie ostatniego sufiksu w drzewie
 * @author: Tomasz Szo�tysek
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

/* Konstruktor iteratora w oparciu o wska�nik na kraw�d�
 * @param x: wska�nik na kraw�d� od kt�rej zaczyna si� sufiks
 * @author: Tomasz Szo�tysek
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

/* Konstruktor iteratora w oparciu o wektor wska�nik�w na kraw�dzie sufiksu
 * @param x: wektor wska�nik�w na kraw�dzie sufiksu
 * @author: Tomasz Szo�tysek
 */
suffixTree::myIterator::myIterator(vector<edgeptr> &x)
{
	p = x;
}

/* Konstruktor iteratora w oparciu o drzewo sufiks�w
 * @param x: drzewo sufiks�w
 * @author: Tomasz Szo�tysek
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

/* operator przypisania wektora wska�nik�w na kraw�dzie sufiksu
 * @param x: wektor wska�nik�w na kraw�dzie sufiksu
 * @author: Tomasz Szo�tysek
 */
void suffixTree::myIterator::operator=(vector<edgeptr> &x) 
{
	p = x;
}

/* operator przypisania innego iteratora
 * @param x: iterator, kt�rego warto�� ma by� przypisana
 * @author: Tomasz Szo�tysek
 */
void suffixTree::myIterator::operator=(myIterator &x) 
{
	vector<edgeptr> q = x.get();
	p.swap(p);
}

/* getter
 * @return: wektor wska�nik�w na kraw�dzie sufiksu, na kt�ry aktualnie wskazuje iterator
 * @author: Tomasz Szo�tysek
 */
const vector<edgeptr> suffixTree::myIterator::get()
{
	return p;
}

/* operator por�wnania z innym iteratorem
 * @param x: iterator do por�wnania
 * @return: true, je�li iteratory wskazuj� na to samo, inaczej false
 * @author: Tomasz Szo�tysek
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

/* operator por�wnania z wektorem wska�nik�w na kraw�dzie sufiksu
 * @param x: wektor kraw�dzi do por�wnania
 * @return: true, je�li iterator zawiera taki sam wektor jak parametr x, inaczej false
 * @author: Tomasz Szo�tysek
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

/* Wyszukiwanie nast�pnika elementu iteratora
 * @return: wska�nik na nast�pnik elementu
 * @author: Tomasz Szo�tysek
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

/* Operator preinkrementacji - wykonuje to samo co next(), tylko bez zwracania warto�ci
 * @author: Tomasz Szo�tysek
 */
void suffixTree::myIterator::operator++()
{
	next();
}

/* Operator postinkrementacji - wykonuje to samo co next(), tylko bez zwracania warto�ci
 * @author: Tomasz Szo�tysek
 */
void suffixTree::myIterator::operator++(int a)
{
	next();
}