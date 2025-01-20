#include <iostream>
#include "JumpListTester.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

	for(int i=1; i<argc; i++) {
		switch (argv[i][0]) {
		case 'a': { JumpListTester t; t.testa(); } break;
		case 'b': { JumpListTester t; t.testb(); } break;
		case 'c': { JumpListTester t; t.testc(); } break;
		case 'd': { JumpListTester t; t.testd(); } break;
		case 'e': { JumpListTester t; t.teste(); } break;
		case 'f': { JumpListTester t; t.testf(); } break;
		case 'g': { JumpListTester t; t.testg(); } break;
		case 'h': { JumpListTester t; t.testh(); } break;
		case 'i': { JumpListTester t; t.testi(); } break;
		case 'j': { JumpListTester t; t.testj(); } break;
		case 'k': { JumpListTester t; t.testk(); } break;
		case 'l': { JumpListTester t; t.testl(); } break;
		case 'm': { JumpListTester t; t.testm(); } break;
		case 'n': { JumpListTester t; t.testn(); } break;
		case 'o': { JumpListTester t; t.testo(); } break;
		case 'p': { JumpListTester t; t.testp(); } break;
		case 'q': { JumpListTester t; t.testq(); } break;
		case 'r': { JumpListTester t; t.testr(); } break;
		case 's': { JumpListTester t; t.tests(); } break;
		case 't': { JumpListTester t; t.testt(); } break;
		case 'u': { JumpListTester t; t.testu(); } break;
		case 'v': { JumpListTester t; t.testv(); } break;
//		case 'w': { JumpListTester t; t.testw(); } break;
//		case 'x': { JumpListTester t; t.testx(); } break;
//		case 'y': { JumpListTester t; t.testy(); } break;
		case 'z': { JumpListTester t; t.testz(); } break;
		default: { cout << "Options are a -- v." << endl; } break;
	       	}
	}
	return 0;
}
