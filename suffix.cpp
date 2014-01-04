#include "suffix.h"

void main() 
{
	suffixTree test1("abckalabt"); //test("abcdekjlgoabmocdeitabcdgn");

	suffixTree::const_iterator sfxit = test1.begin();

	while(!(sfxit == test1.end()))
	{
		sfxit.draw_sfx();
		sfxit++;
	}

	system("pause");
	
}