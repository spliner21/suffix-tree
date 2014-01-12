#pragma once

#include "edge.h"
#include <vector>

typedef shared_ptr<edge> edgeptr;	// typ wskaŸnika na krawêdŸ

/* Klasa drzewa sufiksów
 * @author: Tomasz Szo³tysek
 */
class suffixTree 
{
private:	
	edgeptr root;	// Korzeñ drzewa - wêze³ z indeksami (-1,-1)
	string sequence;	// Tekst s³owa dla którego utworzono drzewo

	/* Klasa const iteratora po sufiksach
	 * @author: Tomasz Szo³tysek
	 */
	class myIterator 
	{
	private:
		vector<edgeptr> p;	// wektor wskaŸników - przechowuje sekwencjê krawêdzi tworz¹cych sufiks
	public:
		myIterator(edgeptr &x);	// konstruktor w oparciu o pierwsz¹ krawêdŸ
		myIterator(suffixTree &x); // konstruktor przekazuj¹cy drzewo
		myIterator(vector<edgeptr> &x);	// konstruktor w oparciu o wektor wskaŸników na krawêdzi

		void operator=(vector<edgeptr> &x);	// operator przypisania dla wektora krawêdzi
		void operator=(myIterator &x);		// operator przypisania iteratora

		const vector<edgeptr> get();		// getter zwracaj¹cy wektor wskaŸników na krawêdzie
	
		bool operator==(myIterator &x);		// operator porównania z innym iteratorem
		bool operator==(vector<edgeptr> &x);	// operator porównania z wektorem krawêdzi

		const vector<edgeptr> next();	// przejœcie na nastêpny sufiks
		
		void operator++();	// operator preinkrementacji
		void operator++(int);	// operator postinkrementacji

		void draw_sfx(string s)	// robocze - wyœwietlanie sufiksu
		{
			vector<edgeptr>::iterator it = p.begin();
			while(it != p.end())
			{
				it->get()->draw(s);
				it++;
			}
			cout << endl;
		}
	};

public:
	typedef myIterator const_iterator;		// definicja typu const_iteratora

	suffixTree();	// konstruktor domyœlny
	suffixTree(const string& sequence);	// konstruktor w oparciu o s³owo
	~suffixTree();	// destruktor domyœlny

	bool findEdge(char c, edgeptr &e);	// wyszukiwanie krawêdzi, która zaczyna siê na znak c
	int commonSize(const string& s, edgeptr& e, int& o);	// sprawdzenie jak d³uga jest czêœæ wspólna krawêdzi e i sufiksu s
	
	const_iterator begin();	// metoda zwracaj¹ca wskaŸnik na pierwszy sufiks w drzewie
	const_iterator end();		// metoda zwracaj¹ca wskaŸnik na warunek stopu w drzewie
	const_iterator back();		// metoda zwracaj¹ca wskaŸnik na ostatni sufiks w drzewie

	edgeptr& getFirst()	// metoda pomocnicza - zwraca wskaŸnik na pierwsz¹ krawêdŸ w drzewie
	{
		return root->childNode;
	}
};
