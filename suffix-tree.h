#pragma once

#include "edge.h"
#include <vector>

typedef shared_ptr<edge> edgeptr;

class suffixTree 
{
private:	
	edgeptr root;
	string sequence;

	class myIterator 
	{
		vector<edgeptr> p;	// wska�nik na element
		public:
			/* konstruktor przekazuj�cy warto�� p */
			myIterator(edgeptr &x);

			/* konstruktor przekazuj�cy drzewo */
			myIterator(suffixTree &x);
			
			/* operator przypisania innego iteratora
			 * @param x - iterator, kt�rego warto�� ma by� przypisana
			 */
			void operator=(vector<edgeptr> &x);
			void operator=(myIterator &x);

			/* getter - zwraca p */
			const vector<edgeptr> get();
		
			/* operator por�wnania z innym iteratorem
			 * @param x - iterator do por�wnania
			 * @return - true, je�li iteratory wskazuj� na to samo, inaczej false
			 */
			bool operator==(myIterator &x);
			bool operator==(vector<edgeptr> &x);


			/* Wyszukiwanie nast�pnika elementu iteratora
			 * @return - wska�nik na nast�pnik elementu
			 */
			const vector<edgeptr> next();

			void operator++();

			void draw_sfx()
			{
				vector<edgeptr>::iterator it = p.begin();
				while(it != p.end())
				{
					it->get()->draw();
					it++;
				}
				cout << endl;
			}
	};

public:
	typedef myIterator const_iterator;

	suffixTree();
	suffixTree(string sequence);
	~suffixTree();

	bool findEdge(char c, edgeptr &e);
	int commonSize(string s, string m, edgeptr& e);
	
	vector<edgeptr> begin();
	vector<edgeptr> end();
	vector<edgeptr> back();

	edgeptr& getFirst()
	{
		return root->childNode;
	}
};
