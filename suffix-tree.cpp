#include "suffix-tree.h"

suffixTree::suffixTree() 
{
	root = make_shared<edge>(edge(-1,-1));
}

suffixTree::suffixTree(string s) 
{
	root = make_shared<edge>(edge(-1,-1));
	// to trzeba przemyœleæ - clue problemu 
	sequence = s;
	edgeptr tmp;
	for(unsigned int i=0; i< s.length(); ++i)
	{
		string subs = s.substr(i,string::npos);

		tmp = root;
		// sprawdzenie, czy od korzenia odchodzi ju¿ sufiks na tê literê
		if(findEdge(s[i],tmp))
		{
			int l = commonSize(subs,s,tmp); // jak d³uga jest czêœæ wspólna sufiksów

			// podzia³ sufiksu na czêœæ wspóln¹ i resztê
			edgeptr bottomEdge = make_shared<edge>(edge(tmp->getStart()+l,tmp->getEnd(), tmp->word.substr(l,string::npos)));
			tmp->setEnd(tmp->getStart()+l);
			tmp->word = tmp->word.substr(0,l);

			// po³¹czenie czêœci krawêdzi sufiksu
			bottomEdge->childNode = tmp->childNode;
			tmp->childNode = bottomEdge;

			// dodanie reszty nowego sufiksu
			edgeptr bottomRight = make_shared<edge>(edge(i+l,s.length(),subs.substr(l,string::npos)));
			bottomEdge->rightNode = bottomRight;
		}
		else 
		{
			tmp = root->childNode;
			if(root->childNode == nullptr)
				root->childNode = make_shared<edge>(edge(i,s.length(),subs));
			else
			{
				edgeptr tmp1 = tmp->rightNode;
				while (tmp1 != nullptr)
				{
					tmp = tmp1;
					tmp1 = tmp->rightNode;
				}
				tmp->rightNode = make_shared<edge>(edge(i,s.length(),subs));
			}
		}
	}
}

suffixTree::~suffixTree() 
{
}


bool suffixTree::findEdge(char c, edgeptr &e)
{
	edgeptr tmp = e->childNode;
	
	while(tmp != nullptr)
	{
		if(sequence[tmp->getStart()] == c)
		{
			e = tmp;
			return true;
		} 
		else
			tmp = tmp->rightNode;
	}
	return false;
}


int suffixTree::commonSize(string s, string m, edgeptr& e)
{
	int si, ei;
	si = e->getStart();
	ei = e->getEnd();
	string subm = m.substr(si,ei - si);
	unsigned int x = s.size() > subm.size() ? subm.size() : s.size();
	unsigned int i = 0;
	for(i=0; i < x; ++i)
	{
		if(s[i] != subm[i])
			return i;
	}
	if(findEdge(s[i],e))
	{
		return commonSize(s.substr(i,string::npos),m,e);
	}
	return i;
}

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

vector<edgeptr> suffixTree::end()
{
	return vector<edgeptr>();
}

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

/* konstruktor przekazuj¹cy drzewo */
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

/* operator przypisania bst_ptr
 * @param x - wartoœæ, na któr¹ ma wskazywaæ p
 */
void suffixTree::myIterator::operator=(vector<edgeptr> &x) 
{
	p = x;
}

/* operator przypisania innego iteratora
 * @param x - iterator, którego wartoœæ ma byæ przypisana
 */
void suffixTree::myIterator::operator=(myIterator &x) 
{
	vector<edgeptr> q = x.get();
	p.swap(p);
}

/* getter - zwraca p */
const vector<edgeptr> suffixTree::myIterator::get()
{
	return p;
}

/* operator porównania z innym iteratorem
 * @param x - iterator do porównania
 * @return - true, jeœli iteratory wskazuj¹ na to samo, inaczej false
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
 * @return - wskaŸnik na nastêpnik elementu
 */
const vector<edgeptr> suffixTree::myIterator::next() 
{
	edgeptr x = p.back();
	p.pop_back();
	if(x == nullptr)
		return vector<edgeptr>();
	if(x->rightNode != nullptr)
	{
		p.push_back(x->rightNode);
		while(x->childNode != nullptr)
		{
			x = x->childNode;
			p.push_back(x);
		}
		return p;
	}
	else return next();
}

void suffixTree::myIterator::operator++()
{
	next();
}