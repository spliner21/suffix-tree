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

		// sprawdzenie, czy od korzenia odchodzi ju¿ sufiks na tê literê
		if(findEdge(s[i],tmp))
		{
			int l = tmp->commonSize(subs,s); // jak d³uga jest czêœæ wspólna sufiksów

			// podzia³ sufiksu na czêœæ wspóln¹ i resztê
			edgeptr bottomEdge = make_shared<edge>(edge(tmp->getStart()+l+1,tmp->getEnd()));
			tmp->setEnd(tmp->getStart()+l);

			// po³¹czenie czêœci krawêdzi sufiksu
			bottomEdge->childNode = tmp->childNode;
			tmp->childNode = bottomEdge;

			// dodanie reszty nowego sufiksu
			edgeptr bottomRight = make_shared<edge>(edge(i+l,s.length()));
			bottomEdge->rightNode = bottomRight;
		}
		else 
		{
			tmp = root->childNode;
			if(root->childNode == nullptr)
				root->childNode = make_shared<edge>(edge(i,s.length()));
			else
			{
				edgeptr tmp1 = tmp->rightNode;
				while (tmp1 != nullptr)
				{
					tmp = tmp1;
					tmp1 = tmp->rightNode;
				}
				tmp->rightNode = make_shared<edge>(edge(i,s.length()));
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
	edgeptr tmp = root->childNode;
	
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