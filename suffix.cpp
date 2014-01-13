#include "suffix.h"


int main(int argc, char* argv[]) 
{
	setlocale (LC_ALL, "");	// polskie znaki w konsoli
	clock_t start,end;
	if(argc < 2)
		return -1;
	ifstream fileIn;
	fileIn.open(argv[1]);

	cout << "Otwieram plik " << argv[1] << endl;

	string s;
	getline (fileIn,s);

	start = clock();
	suffixTree test(s); //test("abcdeabfgabhiabcjk");
	end = clock();

	cout << "Drzewo sufiksów stworzono w czasie: " << (float)(end-start)/CLOCKS_PER_SEC << "s.\n\n";
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
	
	return 0;
}