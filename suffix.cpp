#include "suffix.h"


void main() 
{
	setlocale (LC_ALL, "");	// polskie znaki w konsoli
	clock_t start,end;

	string s = "Jest taki dzien, bardzo cieply, choc grudniowy, Dzien, zwykly dzien, w ktorym gasna wszelkie spory. Jest taki dzien, w ktorym radosc wita wszystkich, Dzien, ktory juz kazdy z nas zna od kolyski.";
	start = clock();
	suffixTree test(s); //test("abcdeabfgabhiabcjk");
	end = clock();

	cout << "Drzewo sufiksów dla zdania: \n" << s << "\nstworzono w czasie: " << (float)(end-start)/CLOCKS_PER_SEC << "s.\n\n";
	suffixTree::const_iterator sfxit = test.begin();

	start = clock();
	while(!(sfxit == test.end()))
	{
		//sfxit.draw_sfx(s);
		sfxit++;
	}
	end = clock();
	cout << "Iteracjê po wszystkich sufiksach drzewa wykonano w czasie: " << (float)(end-start)/CLOCKS_PER_SEC << "s.\n\n";

	cout << endl;

	system("pause");
	
}