#pragma once

#include "edge.h"
#include <vector>

typedef shared_ptr<edge> edgeptr;	// typ wska�nika na kraw�d�

/* Klasa drzewa sufiks�w
 * @author: Tomasz Szo�tysek
 */
class suffixTree 
{
private:	
	edgeptr root;	// Korze� drzewa - w�ze� z indeksami (-1,-1)
	string sequence;	// Tekst s�owa dla kt�rego utworzono drzewo

	/* Klasa const iteratora po sufiksach
	 * @author: Tomasz Szo�tysek
	 */
	class myIterator 
	{
	private:
		vector<edgeptr> p;	// wektor wska�nik�w - przechowuje sekwencj� kraw�dzi tworz�cych sufiks
	public:
		myIterator(edgeptr &x);	// konstruktor w oparciu o pierwsz� kraw�d�
		myIterator(suffixTree &x); // konstruktor przekazuj�cy drzewo
		myIterator(vector<edgeptr> &x);	// konstruktor w oparciu o wektor wska�nik�w na kraw�dzi

		void operator=(vector<edgeptr> &x);	// operator przypisania dla wektora kraw�dzi
		void operator=(myIterator &x);		// operator przypisania iteratora

		const vector<edgeptr> get();		// getter zwracaj�cy wektor wska�nik�w na kraw�dzie
	
		bool operator==(myIterator &x);		// operator por�wnania z innym iteratorem
		bool operator==(vector<edgeptr> &x);	// operator por�wnania z wektorem kraw�dzi

		const vector<edgeptr> next();	// przej�cie na nast�pny sufiks
		
		void operator++();	// operator preinkrementacji
		void operator++(int);	// operator postinkrementacji

		void draw_sfx(string s)	// robocze - wy�wietlanie sufiksu
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

	suffixTree();	// konstruktor domy�lny
	suffixTree(const string& sequence);	// konstruktor w oparciu o s�owo
	~suffixTree();	// destruktor domy�lny

	bool findEdge(char c, edgeptr &e);	// wyszukiwanie kraw�dzi, kt�ra zaczyna si� na znak c
	int commonSize(const string& s, edgeptr& e, int& o);	// sprawdzenie jak d�uga jest cz�� wsp�lna kraw�dzi e i sufiksu s
	
	const_iterator begin();	// metoda zwracaj�ca wska�nik na pierwszy sufiks w drzewie
	const_iterator end();		// metoda zwracaj�ca wska�nik na warunek stopu w drzewie
	const_iterator back();		// metoda zwracaj�ca wska�nik na ostatni sufiks w drzewie

	edgeptr& getFirst()	// metoda pomocnicza - zwraca wska�nik na pierwsz� kraw�d� w drzewie
	{
		return root->childNode;
	}
};
