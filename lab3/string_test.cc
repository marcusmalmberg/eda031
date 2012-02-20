#include <cassert>
#include <iostream>

using namespace std;

void replace_all(string& s, const string& from, const string& to) {
	size_t pos = 0;

	while(true) {
		// Find next occurance of the needle
		pos = s.find(from, pos); 

		// If the needle wasn't found exit the loop
		if(pos == string::npos) {
			break;
		}

		// Replace the needle with the new content
		s.replace(pos, from.size(), to);

		// Set the search position after the new content
		pos += to.size();
	}
}

string primes(int ceiling) {
	// Init string with P and mark 0 and 1 as not primes
	string primeString = string(ceiling, 'P');
	primeString[0] = 'C';
	primeString[1] = 'C';

	// Replace every mulitple with C
	for(size_t i = 2; i < primeString.size(); ++i) {
		size_t j = 2;
		while(i*j < primeString.size()) {
			primeString[i*j] = 'C';
			++j;
		}
	}

	// Return resulting string
	return primeString;
}

int print_largest_prime(int ceiling) {
	// Get string with primes and return the position of the last occurance of 'P'
	string pri = primes(ceiling);
	return pri.rfind('P');
}

int main() {
	cout << "Testing replace_all." << endl;
	string text = "A man, a plan, a canal, Panama!";
	replace_all(text, "an", "XXX");
	assert(text == "A mXXX, a plXXX, a cXXXal, PXXXama!");
	text = "ananan";
	replace_all(text, "an", "XXX");
	assert(text == "XXXXXXXXX");
	text = "ananan";
	replace_all(text, "an", "anan");
	assert(text == "anananananan");
	cout << "Success: All assertions return true." << endl << endl;

	int nPrimesToPrint = 200;
	cout << "Printing primes from 0 to " << nPrimesToPrint << endl;
	cout << primes(nPrimesToPrint) << endl << endl;
	
	int largestPrimeCeiling = 100000;
	cout << "Printing largest prime less than " << largestPrimeCeiling << endl;
	cout << print_largest_prime(largestPrimeCeiling) << endl;
}
