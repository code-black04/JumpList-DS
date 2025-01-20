#include <iostream>
#include "JumpListTester.h"
#include "JumpList.h"

using namespace std;

JumpListTester::JumpListTester() : error_(false), funcname_("") {}

// default ctor and size
void JumpListTester::testa() {
	funcname_ = "JumpListTester::testa";
	{

	JumpList a;
	if (a.size() != 0)
		errorOut_("def ctor wrong size: ", a.size(), 0);

	}
	passOut_();
}

// size using param ctor
void JumpListTester::testb() {
	funcname_ = "JumpListTester::testb";
	{

	JumpList a(1);
	if (a.size() != 1)
		errorOut_("size-1 param ctor wrong size: ", a.size(), 1);

	JumpList b(3);
	if (b.size() != 3)
		errorOut_("size-3 param ctor wrong size: ", b.size(), 1);

	JumpList c(10);
	if (c.size() != 10)
		errorOut_("size-10 param ctor wrong size: ", c.size(), 2);

	string arr[]{"1","2","3","4"};
	JumpList d(4, arr);
	if (d.size() != 4)
		errorOut_("size-4 param ctor wrong size: ", d.size(), 2);

	}
	passOut_();
}

// find
// as long as your ctor is correct it should pass since find() is already done for you
void JumpListTester::testc() {
	funcname_ = "JumpListTester::testc";
	{

	JumpList a;
	if (a.find("qqq")) errorOut_("found something in empty list", 1);

	JumpList b(3);
	if (!b.find("a")) errorOut_("did not find a when present", 1);
	if (!b.find("b")) errorOut_("did not find b when present", 1);
	if (!b.find("blah")) errorOut_("did not find blah when present", 1);
	if (b.find("0")) errorOut_("found 0 when absent", 1);
	if (b.find("aaa")) errorOut_("found aaa when absent", 1);
	if (b.find("zzz")) errorOut_("found zzz when absent", 1);

	JumpList c(10);
	if (!c.find("cat")) errorOut_("did not find cat when present", 2);
	if (!c.find("d")) errorOut_("did not find d when present", 2);
	if (!c.find("ooo...")) errorOut_("did not find ooo... when present", 2);
	if (!c.find("x")) errorOut_("did not find x when present", 2);
	if (!c.find("zzz")) errorOut_("did not find zzz when present", 2);
	if (c.find("dog")) errorOut_("found dog when absent", 2);
	if (c.find("zzzz")) errorOut_("found zzzz when absent", 2);

	}
	passOut_();
}

// get
void JumpListTester::testd() {
	funcname_ = "JumpListTester::testd";
	{

	const string arr[]{"a", "bb", "ccc", "d", "ee", "fff", "g", "hh", "iii", "j", "kk", "lll"};

	JumpList a(12, arr);
	for(int i = 0; i < 12; i++) {
		if (a.get(i) != arr[i])
			errorOut_("wrong get at i="+std::to_string(i)+": ", a.get(i), 0);
	}

	}
	passOut_();
}

// get oob
void JumpListTester::teste() {
	funcname_ = "JumpListTester::teste";
	{

	string s;

	JumpList a(10);
	s = a.get(-1);
	if (s != "") errorOut_("get out of bounds -1 wrong: ", s, 1);
	s = a.get(10);
	if (s != "") errorOut_("get out of bounds 10 wrong: ", s, 1);

	JumpList b;
	s = b.get(0);
	if (s != "") errorOut_("get out of bounds wrong for empty jumplist: ", s, 2);

	}
	passOut_();
}

// print
void JumpListTester::testf() {
	funcname_ = "JumpListTester::testf";
	{

	string s, ans;

	// 1-node list
	JumpList a(1);
	s = a.print();
	ans = "a\na\n1";
	if (s != ans)
		errorOut_("print size-1 JumpList wrong", ans, s, 1);

	// 3-node list
	JumpList b(3);
	s = b.print();
	ans = "a b blah\na\n3";
	if (s != ans)
		errorOut_("print size-3 JumpList wrong", ans, s, 2);

	}
	passOut_();
}

// more print
void JumpListTester::testg() {
	funcname_ = "JumpListTester::testg";
	{

	string s, ans;

	// empty list
	JumpList a;
	s = a.print();
	ans = "\n\n";
	if (s != ans)
		errorOut_("print empty JumpList wrong", ans, s, 1);

	// 10-node list
	JumpList b(10);
	s = b.print();
	ans = "a b blah c cat d etc ooo... x zzz\na d x\n5 3 2";
	if (s != ans)
		errorOut_("print size-10 JumpList wrong", ans, s, 2);

	// custom list
	string arr[]{"a","b","c","d","e","f","g","h","i","j"};
	JumpList c(10, arr);
	s = c.print();
	ans = "a b c d e f g h i j\na f\n5 5";
	if (s != ans)
		errorOut_("print custom JumpList wrong", ans, s, 2);


	}
	passOut_();
}

// simple insert
void JumpListTester::testh() {
	funcname_ = "JumpListTester::testh";
	{

	// insert to empty list
	JumpList a;
	a.insert("a");
	if (a.size() != 1)
		errorOut_("insert a wrong size: ", a.size(), 1);
	if (!a.find("a"))
		errorOut_("cannot find a after insert", 1);
	if (a.get(0) != "a")
		errorOut_("insert a wrong get: ", a.get(0), 1);

	// append to size-3 list
	JumpList b(3);
	b.insert("c");
	if (b.size() != 4)
		errorOut_("insert c wrong size: ", b.size(), 2);
	if (!b.find("c"))
		errorOut_("cannot find c", 2);
	if (b.get(3) != "c")
		errorOut_("insert c wrong get: ", b.get(3), 2);

	}
	passOut_();
}

// insert at various places (non-alpha order); print and get
void JumpListTester::testi() {
	funcname_ = "JumpListTester::testi";
	{

	string s, ans;
	JumpList a;

	// insert to empty
	a.insert("d");
	s = a.print();
	ans = "d\nd\n1";
	if (s != ans)
		errorOut_("insert d wrong print", ans, s, 1);

	// insert to front
	a.insert("b");
	s = a.print();
	ans = "b d\nb\n2";
	if (s != ans)
		errorOut_("insert b wrong print", ans, s, 1);

	// end
	a.insert("f");
	s = a.print();
	ans = "b d f\nb\n3";
	if (s != ans)
		errorOut_("insert f wrong print", ans, s, 1);

	// second
	a.insert("c");
	s = a.print();
	ans = "b c d f\nb\n4";
	if (s != ans)
		errorOut_("insert c wrong print", ans, s, 1);

	// second from end
	a.insert("e");
	s = a.print();
	ans = "b c d e f\nb\n5";
	if (s != ans)
		errorOut_("insert e wrong print", ans, s, 1);

	// various gets
	if (a.get(0) != "b")
		errorOut_("get0 wrong: ", a.get(0), 2);
	if (a.get(1) != "c")
		errorOut_("get1 wrong: ", a.get(1), 2);
	if (a.get(2) != "d")
		errorOut_("get2 wrong: ", a.get(2), 2);
	if (a.get(3) != "e")
		errorOut_("get3 wrong: ", a.get(3), 2);
	if (a.get(4) != "f")
		errorOut_("get4 wrong: ", a.get(4), 2);


	}
	passOut_();
}

// insert to multi-segment lists
void JumpListTester::testj() {
	funcname_ = "JumpListTester::testj";
	{

	string s, ans;

	// insert to middle segment, edges
	JumpList a(10);
	a.insert("dog");
	if (a.size() != 11)
		errorOut_("insert dog wrong size: ", a.size(), 1);
	if (!a.find("dog"))
		errorOut_("cannot find dog", 1);
	s = a.print();
	ans = "a b blah c cat d dog etc ooo... x zzz\na d x\n5 4 2";
	if (s != ans)
		errorOut_("insert dog wrong print", ans, s, 2);

	JumpList b(10);
	b.insert("p");
	if (b.size() != 11)
		errorOut_("insert p wrong size: ", b.size(), 1);
	if (!b.find("p"))
		errorOut_("cannot find p", 1);
	s = b.print();
	ans = "a b blah c cat d etc ooo... p x zzz\na d x\n5 4 2";
	if (s != ans)
		errorOut_("insert p wrong print", ans, s, 2);

	// last segment
	JumpList c(10);
	c.insert("y");
	if (c.size() != 11)
		errorOut_("insert y wrong size: ", c.size(), 1);
	if (!c.find("y"))
		errorOut_("cannot find y", 1);
	s = c.print();
	ans = "a b blah c cat d etc ooo... x y zzz\na d x\n5 3 3";
	if (s != ans)
		errorOut_("insert y wrong print", ans, s, 2);

	}
	passOut_();
}

// insert ret val, element already exist
void JumpListTester::testk() {
	funcname_ = "JumpListTester::testk";
	{

	JumpList a(3);
	if (a.insert("a"))
		errorOut_("returned true when insert a again", 1);
	if (a.insert("b"))
		errorOut_("returned true when insert b again", 1);
	if (a.insert("blah"))
		errorOut_("returned true when insert blah again", 1);
	if (a.size() != 3)
		errorOut_("a wrong size after 3 non-insert: ", a.size(), 1);

	if (!a.insert("aaa"))
		errorOut_("returned false when insert aaa", 1);

	// longer list
	JumpList b(10);
	if (b.insert("etc"))
		errorOut_("returned true when insert etc again", 2);
	if (b.insert("zzz"))
		errorOut_("returned true when insert zzz again", 2);
	if (b.insert("x"))
		errorOut_("returned true when insert x again", 2);
	if (b.size() != 10)
		errorOut_("b wrong size after 3 non-insert: ", b.size(), 2);

	if (!b.insert("y"))
		errorOut_("returned false when insert y", 2);

	}
	passOut_();
}

// insert with split (one segment)
void JumpListTester::testl() {
	funcname_ = "JumpListTester::testl";
	{

	string s, ans;

	// repeatedly insert to front of list
	JumpList a;
	a.insert("f");
	a.insert("e");
	a.insert("c");
	a.insert("b");
	a.insert("a");

	// check that 5 does not split yet
	s = a.print();
	ans = "a b c e f\na\n5";
	if (s != ans)
		errorOut_("wrong print at size 5", ans, s, 1);

	if (!a.insert("d")) // check ret val w splits
		errorOut_("wrong bool: ", 1);

	if (a.size() != 6)
		errorOut_("wrong size: ", a.size(), 2);
	if (!a.find("d"))
		errorOut_("cannot find d", 2);
	if (!a.find("f"))
		errorOut_("cannot find tail", 2);
	s = a.print();
	ans = "a b c d e f\na d\n3 3"; // even division, also inserted node happens to be the new jump node
	if (s != ans)
		errorOut_("wrong print at size 6", ans, s, 2);

	}
	passOut_();
}

// insert split in multiple segment lists; edge cases within a segment
void JumpListTester::testm() {
	funcname_ = "JumpListTester::testm";
	{

	string s, ans;

	// first segment, head
	JumpList a(10);
	a.insert("A");
	if (a.size() != 11)
		errorOut_("insert to a wrong size: ", a.size(), 1);
	if (!a.find("A"))
		errorOut_("insert to a cannot find A", 1);
	if (!a.find("zzz"))
		errorOut_("insert to a cannot find tail", 1);
	s = a.print();
	ans = "A a b blah c cat d etc ooo... x zzz\nA blah d x\n3 3 3 2";
	if (s != ans)
		errorOut_("insert to a wrong print", ans, s, 1);

	// middle segment including edges
	JumpList b(10);
	b.insert("f");
	b.insert("p");
	b.insert("dog");
	if (b.size() != 13)
		errorOut_("insert to b wrong size: ", b.size(), 2);
	if (!b.find("p"))
		errorOut_("insert to b cannot find p", 2);
	s = b.print();
	ans = "a b blah c cat d dog etc f ooo... p x zzz\na d f x\n5 3 3 2";
	if (s != ans)
		errorOut_("insert to b wrong print", ans, s, 2);

	// end of list
	string arr[]{"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O"};
	JumpList c(15, arr);
	c.insert("P");
	if (c.size() != 16)
		errorOut_("insert to c wrong size: ", c.size(), 2);
	if (!c.find("P"))
		errorOut_("insert to c cannot find K", 2);
	s = c.print();
	ans = "A B C D E F G H I J K L M N O P\nA F K N\n5 5 3 3";
	if (s != ans)
		errorOut_("insert to c wrong print", ans, s, 2);

	}
	passOut_();
}

// simple erase
void JumpListTester::testn() {
	funcname_ = "JumpListTester::testn";
	{

	// empty list
	JumpList a;
	a.erase("a");
	if (a.size() != 0)
		errorOut_("erase from empty list wrong size: ", a.size(), 1);
	if (a.find("a"))
		errorOut_("erase from empty list found something?!", 1);
	if (a.get(0) != "")
		errorOut_("erase from empty list wrong get(0): ", a.get(0), 1);

	// one element
	JumpList b(1);
	b.erase("a");
	if (b.size() != 0)
		errorOut_("erase from size-1 list wrong size: ", b.size(), 1);
	if (b.find("a"))
		errorOut_("erase from size-1 list still found", 1);
	if (b.get(0) != "")
		errorOut_("erase from size-1 list wrong get(0): ", b.get(0), 1);

	// three elements, middle, tail
	JumpList c(3);
	c.erase("b");
	if (c.size() != 2)
		errorOut_("erase from size-3 list wrong size: ", c.size(), 2);
	if (c.find("b"))
		errorOut_("erase from size-3 list still found", 2);
	if (c.get(1) != "blah")
		errorOut_("erase from size-3 list wrong get(1): ", c.get(1), 2);

	c.erase("blah");
	if (c.size() != 1)
		errorOut_("erase from size-2 list wrong size: ", c.size(), 2);
	if (c.find("blah"))
		errorOut_("erase from size-2 list still found", 2);
	if (c.get(0) != "a")
		errorOut_("erase from size-2 list wrong get(0): ", c.get(0), 2);

	}
	passOut_();
}

// erase, longer list but non-jump nodes only
void JumpListTester::testo() {
	funcname_ = "JumpListTester::testo";
	{

	string s, ans;

	// first segment
	JumpList a(10);
	a.erase("blah");
	if (a.find("blah"))
		errorOut_("erase blah still present", 1);
	if (!a.find("zzz"))
		errorOut_("erase blah can't find tail", 1);
	if (a.get(2) != "c")
		errorOut_("erase blah wrong get(2): ", a.get(2), 1);
	s = a.print();
	ans = "a b c cat d etc ooo... x zzz\na d x\n4 3 2";
	if (s != ans)
		errorOut_("erase blah wrong print", ans, s, 1);

	// later segments
	// just after jump node
	JumpList b(10);
	b.erase("etc");
	if (b.find("etc"))
		errorOut_("erase etc still present", 2);
	if (!b.find("zzz"))
		errorOut_("erase etc can't find tail", 2);
	if (b.get(6) != "ooo...")
		errorOut_("erase etc wrong get(6): ", b.get(6), 2);
	s = b.print();
	ans = "a b blah c cat d ooo... x zzz\na d x\n5 2 2";
	if (s != ans)
		errorOut_("erase etc wrong print", ans, s, 2);

	// just before jump node
	JumpList c(10);
	c.erase("ooo...");
	if (c.find("ooo..."))
		errorOut_("erase ooo... still present", 2);
	if (!c.find("zzz"))
		errorOut_("erase ooo... can't find tail", 2);
	if (c.get(7) != "x")
		errorOut_("erase ooo... wrong get(7): ", c.get(7), 2);
	s = c.print();
	ans = "a b blah c cat d etc x zzz\na d x\n5 2 2";
	if (s != ans)
		errorOut_("erase cat wrong print", ans, s, 2);

	// end of list (note segment still has length 1 after erase)
	JumpList d(10);
	d.erase("zzz");
	if (d.find("zzz"))
		errorOut_("erase zzz still present", 2);
	if (!d.find("x"))
		errorOut_("erase zzz can't find tail", 2);
	if (d.get(8) != "x")
		errorOut_("erase zzz wrong get(8): ", d.get(8), 2);
	s = d.print();
	ans = "a b blah c cat d etc ooo... x\na d x\n5 3 1";
	if (s != ans)
		errorOut_("erase zzz wrong print", ans, s, 2);

	}
	passOut_();
}

// erasing jump nodes w/o triggering split
void JumpListTester::testp() {
	funcname_ = "JumpListTester::testp";
	{

	string s, ans;

	// merging last two segments
	// just below split triggering size
	JumpList a(10);
	a.erase("x");
	if (a.size() != 9)
		errorOut_("erase x wrong size: ", a.size(), 1);
	if (a.find("x"))
		errorOut_("erase x still found x", 1);
	if (!a.find("zzz"))
		errorOut_("erase x can't find tail", 1);
	s = a.print();
	ans = "a b blah c cat d etc ooo... zzz\na d\n5 4";
	if (s != ans)
		errorOut_("erase x wrong print", ans, s, 1);

	// merging first two segments
	// erase something else first to avoid split
	JumpList b(10);
	b.erase("b");
	b.erase("blah");
	b.erase("d");
	if (b.size() != 7)
		errorOut_("erase d wrong size: ", b.size(), 2);
	if (b.find("d"))
		errorOut_("erase d still found d", 2);
	if (!b.find("zzz"))
		errorOut_("erase d can't find tail", 2);
	s = b.print();
	ans = "a c cat etc ooo... x zzz\na x\n5 2";
	if (s != ans)
		errorOut_("erase d wrong print", ans, s, 2);

	}
	passOut_();
}

// erase ret val, non-existent element
void JumpListTester::testq() {
	funcname_ = "JumpListTester::testq";
	{

	JumpList a;
	if (a.erase("a"))
		errorOut_("returned true when erasing from empty", 1);

	JumpList b(1);
	if (b.erase("A"))
		errorOut_("returned true when erasing nonexistent A", 1);
	if (b.size() != 1)
		errorOut_("wrong size after 1 non-erase: ", b.size(), 1);
	if (!b.erase("a"))
		errorOut_("returned false when erasing a", 1);

	// longer list including jump nodes
	JumpList c(10);
	if (c.erase("y"))
		errorOut_("returned true when erasing non-existent y", 2);
	if (c.erase("e"))
		errorOut_("returned true when erasing non-existent e", 2);
	if (c.size() != 10)
		errorOut_("wrong size after 2 non-erase: ", c.size(), 2);

	if (!c.erase("d"))
		errorOut_("returned false when erasing d", 2);
	if (!c.erase("x"))
		errorOut_("returned false when erasing x", 2);

	}
	passOut_();
}

// erase w/ splits
void JumpListTester::testr() {
	funcname_ = "JumpListTester::testr";
	{

	string s, ans;

	// first two segments
	// erase something else first to achieve even size
	JumpList a(10);
	a.erase("b");
	a.erase("d");
	if (a.size() != 8)
		errorOut_("erase from a wrong size: ", a.size(), 1);
	if (a.find("d"))
		errorOut_("erase from a still found d", 1);
	if (!a.find("zzz"))
		errorOut_("erase from a can't find tail", 1);
	s = a.print();
	ans = "a blah c cat etc ooo... x zzz\na cat x\n3 3 2";
	if (s != ans)
		errorOut_("erase from a wrong print", ans, s, 1);

	// last two segments, custom input
	// just at triggering size, also checks odd length split
	string arr[]{"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o"};
	JumpList b(15, arr);
	b.erase("k");
	if (b.size() != 14)
		errorOut_("erase from b wrong size: ", b.size(), 2);
	if (b.find("k"))
		errorOut_("erase from b still found d", 2);
	if (!b.find("o"))
		errorOut_("erase from b can't find tail", 2);
	s = b.print();
	ans = "a b c d e f g h i j l m n o\na f l\n5 5 4";
	if (s != ans)
		errorOut_("erase from b wrong print", ans, s, 2);

	}
	passOut_();
}

// erase head of list
void JumpListTester::tests() {
	funcname_ = "JumpListTester::tests";
	{

	string s, ans;

	// one segment
	JumpList a(3);
	a.erase("a");
	if (a.size() != 2)
		errorOut_("erase head from a wrong size: ", a.size(), 1);
	if (a.find("a"))
		errorOut_("erase head from a still found", 1);
	if (!a.find("blah"))
		errorOut_("erase head from a can't find tail", 1);
	s = a.print();
	ans = "b blah\nb\n2";
	if (s != ans)
		errorOut_("erase head from a wrong print", ans, s, 1);

	// more segments
	JumpList b(10);
	b.erase("a");
	if (b.size() != 9)
		errorOut_("erase head from b wrong size: ", a.size(), 2);
	if (b.find("a"))
		errorOut_("erase head from b still found", 2);
	if (!b.find("zzz"))
		errorOut_("erase head from b can't find tail", 2);
	s = b.print();
	ans = "b blah c cat d etc ooo... x zzz\nb d x\n4 3 2";
	if (s != ans)
		errorOut_("erase head from b wrong print", ans, s, 2);

	}
	passOut_();
}

// erase edge cases: with size-1 segments
void JumpListTester::testt() {
	funcname_ = "JumpListTester::testt";
	{

	string s, ans;

	JumpList a(10);
	// erase others first
	a.erase("b");
	a.erase("blah");
	a.erase("c");
	a.erase("cat");
	a.erase("etc");
	a.erase("ooo...");
	a.erase("zzz");
	// now 1-1-1
	if (a.size() != 3)
		errorOut_("erase 7 others wrong size: ", a.size(), 1);
	s = a.print();
	ans = "a d x\na d x\n1 1 1";
	if (s != ans)
		errorOut_("erase 7 others wrong print", ans, s, 1);

	// first segment length-1 erase
	a.erase("a");
	if (a.size() != 2)
		errorOut_("erase a wrong size: ", a.size(), 1);
	s = a.print();
	ans = "d x\nd x\n1 1";
	if (s != ans)
		errorOut_("erase a wrong print", ans, s, 1);

	// last segment length-1 erase
	a.erase("x");
	if (a.size() != 1)
		errorOut_("erase x wrong size: ", a.size(), 2);
	s = a.print();
	ans = "d\nd\n1";
	if (s != ans)
		errorOut_("erase x wrong print", ans, s, 2);

	// erase to empty
	a.erase("d");
	if (a.size() != 0)
		errorOut_("erase d wrong size: ", a.size(), 2);
	s = a.print();
	ans = "\n\n";
	if (s != ans)
		errorOut_("erase d wrong print", ans, s, 2);

	}
	passOut_();
}

// prettyprint
void JumpListTester::testu() {
	funcname_ = "JumpListTester::testu";
	{

	string s, ans, ans1, ans2, ans3;

	JumpList a(3);
	s = a.prettyPrint();
	ans1 = "a --> b --> blah";
	ans2 = "a";
	ans3 = "3";
	ans = ans1 + "\n" + ans2 + "\n" + ans3;
	if (s != ans)
		errorOut_("prettyprint size-3 wrong", ans, s, 1);

	JumpList b(10);
	s = b.prettyPrint();
	ans1 = "a --> b --> blah --> c --> cat --> d --> etc --> ooo... --> x --> zzz";
	ans2 = "a -------------------------------> d ---------------------> x";
	ans3 = "5                                  3                        2";
	ans = ans1 + "\n" + ans2 + "\n" + ans3;
	if (s != ans)
		errorOut_("prettyprint size-10 wrong", ans, s, 2);

	}
	passOut_();
}

// more prettyprint
// test alignment with longer words at jump node
void JumpListTester::testv() {
	funcname_ = "JumpListTester::testv";
	{

	string s, ans, ans1, ans2, ans3;

	string arr[]{"AA", "B", "CCC", "D", "EE", "FFFF", "g", "hh", "iii", "j", "kk", "lll"};
	JumpList a(12, arr);
	s = a.prettyPrint();
	ans1 = "AA --> B --> CCC --> D --> EE --> FFFF --> g --> hh --> iii --> j --> kk --> lll";
	ans2 = "AA -----------------------------> FFFF -----------------------------> kk";
	ans3 = "5                                 5                                   2";
	ans = ans1 + "\n" + ans2 + "\n" + ans3;
	if (s != ans)
		errorOut_("prettyprint size-12 wrong", ans, s, 1);

	JumpList b(10, arr);
	s = b.prettyPrint();
	ans1 = "AA --> B --> CCC --> D --> EE --> FFFF --> g --> hh --> iii --> j";
	ans2 = "AA -----------------------------> FFFF";
	ans3 = "5                                 5";
	ans = ans1 + "\n" + ans2 + "\n" + ans3;
	if (s != ans)
		errorOut_("prettyprint size-10 wrong", ans, s, 2);

	JumpList c(1, arr);
	s = c.prettyPrint();
	ans1 = "AA";
	ans2 = "AA";
	ans3 = "1";
	ans = ans1 + "\n" + ans2 + "\n" + ans3;
	if (s != ans)
		errorOut_("prettyprint size-1 wrong", ans, s, 2);


	}
	passOut_();
}

void JumpListTester::errorOut_(const string& errMsg, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void JumpListTester::errorOut_(const string& errMsg, int errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << std::to_string(errResult) << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void JumpListTester::errorOut_(const string& errMsg, const string& errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << errResult << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void JumpListTester::errorOut_(const string& errMsg, const string& expResult, const string& errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << endl;
	cerr << "Expected output:\n" << expResult << endl;
	cerr << "Your output:\n" << errResult << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void JumpListTester::passOut_() {

	if (!error_) {
		cerr << funcname_ << ":" << " pass" << endl;
	}
	cerr << std::flush;
}