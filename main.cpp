#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

namespace helper{
	// Converts the given string to a int
	int strToNum(string strNum)
	{
		stringstream streamNum (strNum);
		int num;
		if (!(streamNum >> num)) {
			num = 0;
		}

		return num;
	}
}


int main(int argc, char * argv[])
{
	// check for if optional parameter is given
	if (argc > 1) {
		// initalize pseudocode random generator
		string strSeed = argv[1];
		int seed = helper::strToNum(strSeed);
		
		srand48(seed);
	}
	
}
