#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
	printf("***** CREATION\n");
	int* tl = new int[3];            // tableau dynamique alloué sur le tas (il faut le libérer)
	tl[0] = 1;
	delete[] tl;

	std::vector<int> ts = { 1,2,3 };          // vector STL alloué de manière cachée dans le tas, le vector gère son allocation et destruction
	std::copy(ts.begin(), ts.end(), std::ostream_iterator<int>(std::cout, " "));


	printf("***** CREATION 2D\n");

	printf("***** COMPTER\n");

	printf("***** SLICING\n");

	printf("***** PERFORMANCE\n");
	vector< vector

	return 0;
}



