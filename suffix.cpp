/// Program testuj¹cy drzewo sufiksów
///
///	autor: Tomasz Szo³tysek
/// grupa IGT :: sem 2MGR 
/// Informatyka :: AEiI Politechnika Œl¹ska
/// 13.01.2014r.

#include "suffix.h"

int main(int argc, char* argv[]) 
{
	setlocale (LC_ALL, "");	// polskie znaki w konsoli
	clock_t start,end;
	
	if(argc < 2)	// Program dzia³a tylko dla zadanego pliku z danymi testowymi
	{
		cout << "Uruchamianie: " << argv[0] << " <nazwa pliku z danymi testowymi>" << endl << "Na przyk³ad:" << endl << argv[0] << " test.txt" << endl;
		return -1;
	}

	ifstream fileIn;		// Otwarcie pliku z danymi testowymi
	fileIn.open(argv[1]);

	cout << "Otwieram plik " << argv[1] << endl;

	string s;
	getline (fileIn,s);	// Plik ma zawieraæ tylko jedn¹ liniê zawieraj¹c¹ dane testowe. Wszystkie pozosta³e linie s¹ ignorowane.

	fileIn.close();

	start = clock();	// Pomiar czasu tworzenia drzewa
	suffixTree test(s);
	end = clock();

	cout << "Drzewo sufiksów stworzono w czasie: " << (float)(end-start)/CLOCKS_PER_SEC << "s.\n\n";
	suffixTree::const_iterator sfxit = test.begin();

	start = clock();	// Pomiar czasu iterowania po drzewie
	while(!(sfxit == test.end()))
	{
		//sfxit.draw_sfx(s);	// Mo¿na wypisywaæ kolejne sufiksy na ekran
		sfxit++;
	}
	end = clock();
	cout << "Iteracjê po wszystkich sufiksach drzewa wykonano w czasie: " << (float)(end-start)/CLOCKS_PER_SEC << "s.\n\n";

	cout << endl;

	system("pause");
	
	return 0;
}