#ifndef JUMPLIST_H_
#define JUMPLIST_H_

#include <string>
using std::string;

class Node {

	string data_; // string element stored at this node
	Node* next_;  // pointer to next node
	Node* jump_;  // pointer to next jump node
	int gap_;     // size of this segment
	              
public:
	// Constructor
	Node(const string& data, Node* next, Node* jump, int gap);

	// Destructor
	~Node();

friend class JumpList; // allows JumpList to access private members
};

class JumpList {

public:
	// Default constructor. Creates an empty JumpList.
	JumpList();

	// Parameterised constructor.
	// If 'arr' is not nullptr, it is assumed to point to a string array
	// of size 'size' with elements already in increasing order,
	// and a JumpList will be created using those elements with
	// a gap size of MAX_GAP_SIZE (except possibly the last one).
	// If 'arr' is null or not supplied, "the runnung example" or
	// a trucated version of it will be created, where 'size' can only
	// be 1, 3 or 10.
	JumpList(int size, const string* arr = nullptr);

	// Destructor
	~JumpList();

	// Returns the number of nodes.
	int size() const;

	// Returns true if s is in the JumpList and false otherwise.
	bool find(const string& s) const;

	// Return the string stored in the i-th node.
	string get(int i) const;

	// Gives a visual output of the JumpList as specified in the
	// assignment specification.
	string print() const;

	// Gives a better visual output of the JumpList
	string prettyPrint() const;

	// Insert s into the JumpList, splitting a segment where necessary
	// as described in the assignment specification.
	// Returns true if successful, false if s is already in the list.
	bool insert(const string& s);

	void updateGapsAndJumpPointers();
	
	void triggerSplit(Node *segmentHead);

    	void triggerSplit();

    	// Remove s from the JumpList, modifying other jump nodes
	// where necessary as described in the assignment specification.
	// Returns true if successful, false if s is not in the list.
	bool erase(const string& s);

	static const int MAX_GAP_SIZE = 5;

private:
	Node* head_; // point to first node
};

#endif
