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
			int x = 2+3;
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