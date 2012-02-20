#include <string>
#include <fstream>
#include "coding.h"
using namespace std;

int main(int argc, char** argv) {
	if (argc == 0) return 1;
	string filename = argv[1];
	ifstream in(filename.c_str());
	ofstream out((filename + ".dec").c_str());
	char c;
	while (true) {
		in.get(c);
		if (!in.good())
			break;
		out << Coding::decode(c);
	}
	in.close();
	out.close();
}
