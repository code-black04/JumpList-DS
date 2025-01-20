#ifndef JUMPLISTTESTER_H_
#define JUMPLISTTESTER_H_
#include <string>
using namespace std;

class JumpListTester {
public:
	JumpListTester();

	// ctor, size, find
	void testa();
	void testb();
	void testc();

	// get
	void testd();
	void teste();

	// print
	void testf();
	void testg();

	// insert
	void testh();
	void testi();
	void testj();
	void testk();
	void testl();
	void testm();

	// erase
	void testn();
	void testo();
	void testp();
	void testq();
	void testr();
	void tests();
	void testt();

	// prettyprint
	void testu();
	void testv();

	// unused
	void testw();
	void testx();
	void testy();
	void testz();

private:

	// four overloaded versions
	void errorOut_(const std::string& errMsg, unsigned int errBit);
	void errorOut_(const std::string& errMsg, int errRes, unsigned int errBit);
	void errorOut_(const std::string& errMsg, const std::string& errRes, unsigned int errBit);
	void errorOut_(const std::string& errMsg, const std::string& expRes, const std::string& errRes, unsigned int errBit);
	void passOut_();

	char error_;
	std::string funcname_;
};

#endif /* JUMPLISTTESTER_H_ */