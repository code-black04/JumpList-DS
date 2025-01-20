#include "JumpList.h"
#include <stdexcept>
#include <iostream>
using namespace std;

Node::Node(const string& s, Node* next = nullptr, Node* jump = nullptr, int gap = 0) 
	:data_(s), next_(next), jump_(jump), gap_(gap)
{}

Node::~Node() {
    next_ = nullptr;
    jump_ = nullptr;
}


JumpList::JumpList() : head_(nullptr) {
}

JumpList::JumpList(int size, const string* arr) {

	const string s[] = {"a", "b", "blah", "c", "cat", "d", "etc", "ooo...", "x", "zzz"};
	const string* sp = (arr == nullptr) ? s : arr;

	Node** npp = new Node*[size];
	npp[size-1] = new Node(sp[size-1], nullptr, nullptr, 0);
	for(int i = size-2; i >= 0; i--)
		npp[i] = new Node(sp[i], npp[i+1], nullptr, 0);

	if (arr == nullptr) {

		if (size==1) npp[0]->gap_ = 1;
		else if (size==3) npp[0]->gap_ = 3;
 		else if (size==10) {
			npp[0]->jump_ = npp[5];
			npp[5]->jump_ = npp[8];
			npp[0]->gap_ = 5;
			npp[5]->gap_ = 3;
			npp[8]->gap_ = 2;
		}
		else throw std::invalid_argument("size must be 1, 3 or 10");

	}
	else {

		// jump node every MAX_GAP_SIZE
		int i;
		for(i=0; i < size-MAX_GAP_SIZE; i += MAX_GAP_SIZE) {
			npp[i]->jump_ = npp[i+MAX_GAP_SIZE];
			npp[i]->gap_ = MAX_GAP_SIZE;
		}
		npp[i]->gap_ = size % MAX_GAP_SIZE;
		if (npp[i]->gap_ == 0) npp[i]->gap_ = MAX_GAP_SIZE; // 0 need to become 5!

	}

	head_ = npp[0];
	delete [] npp; // note that the local array npp gets destroyed here but the nodes stay alive!

}

JumpList::~JumpList() {

	Node* current = head_;
	while (current != nullptr) {
		Node* toDelete = current;
		current = current->next_;
		delete toDelete;
	}
}


int JumpList::size() const {
    int count = 0;
    Node* current = head_;
    while (current != nullptr) {
        count += current->gap_;
        (current->jump_ != nullptr) ? current = current->jump_: current = current->next_;
    }
    return count;
}

bool JumpList::find(const string& s) const {

	if (head_ == nullptr) return false;

	// moving along the fast lane
	Node* tmp = head_;
	while(tmp->jump_ != nullptr && tmp->jump_->data_ < s)
		tmp = tmp->jump_;

	// tmp now points to the jump node at the start of the segment where s could be

	// now slow lane
	while(tmp != nullptr) {

		if (tmp->data_ == s) return true; // match
		else if (tmp->data_ > s) return false; // went past without finding s
		else tmp = tmp->next_;
	}

	return false; // end of list
}

string JumpList::get(int i) const {
    if (i < 0) return "";
    
    Node* current = head_;
    int count = 0;
    while (current != nullptr) {
        if (count + current->gap_ > i) {
            while (current != nullptr && count < i) {
                current = current->next_;
                count++;
            }
            return (current != nullptr) ? current->data_ : "";
        }
        count += current->gap_;
        current = current->jump_;
    }

    return "";
}

string JumpList::print() const {
    if (head_ == nullptr) {
        return "\n\n";
    }

    string allData;
    string jumpNodes;
    string gaps;
    
    Node* current = head_;
    Node* jumpNode = head_;

    while (current != nullptr) {
        allData += current->data_;
        current = current->next_;
        if (current != nullptr) {
            allData += " ";
        }
    }

    current = head_;
    while (current != nullptr) {
        if (current == jumpNode) {
            jumpNodes += current->data_;
            gaps += std::to_string(current->gap_);
            jumpNode = jumpNode->jump_; 
            if (jumpNode != nullptr) {
                jumpNodes += " ";
                gaps += " "; 
            }
        }
        current = current->next_;
    }

    return allData + "\n" + jumpNodes + "\n" + gaps;
}

string JumpList::prettyPrint() const {
    if (head_ == nullptr) {
        return "\n\n";
    }

    string allData;
    string arrows;
    string jumpArrows;
    string gapSizes;

    Node* current = head_;
    Node* jumpNode = head_;

    // Construct `allData` and `arrows` strings with appropriate separators
    while (current != nullptr && current->next_ != nullptr) {
        allData += current->data_;
        allData += " --> ";
        current = current->next_;
    }

    allData += current->data_; // Add the last node's data without an arrow

    // Construct `jumpArrows` and `gapSizes`, aligning them with `allData` and `arrows`
    current = head_;
    while (current != nullptr) {
        string dataStr = current->data_;

        // If current node is a jump node
        if (current == jumpNode) {
            jumpArrows += dataStr;  // Start jump arrow with the `jumpNode`'s data
            
            size_t jumpLength = 0;
            Node* temp = current;

            // Calculate the span of the jump arrow to the target jump node, without extra spaces
            while (temp != jumpNode->jump_ && temp != nullptr) {
                jumpLength += temp->data_.length();  // Only count the data length
                if (temp->next_ != nullptr && temp != jumpNode->jump_) {
                    jumpLength += 5;  // Account for " --> " only between nodes
                }
                temp = temp->next_;
            }

            // Fill the remaining part of the jump arrow with "-"
            if (jumpNode ->jump_ != nullptr) {
                jumpArrows += " " + string(jumpLength - dataStr.length()-3, '-') + "> ";
            }
            jumpNode = jumpNode->jump_;  // Move to the next jump node

            // Align gapSizes with the start of the jump
            gapSizes += to_string(current->gap_);
            if (current->jump_!=nullptr)
            {
            
            gapSizes += string(jumpLength - to_string(current->gap_).length(), ' ');  // Align gap size under jump arrow
            }
            
            
        } 

        // Add spaces for the " --> " separator if there's a next node
        if (current->next_ != nullptr) {
            jumpArrows += "";
            gapSizes += "";
        }

        current = current->next_;
    }

    return allData + arrows + "\n" + jumpArrows + "\n" + gapSizes;
}

bool JumpList::insert(const string& s) {
    if (find(s)) return false;
    Node* newNode = new Node(s);
    if (head_ == nullptr || head_->data_ > s) {
        newNode->next_ = head_;
        if (head_ != nullptr) {
            newNode->jump_= head_->jump_;
            head_->jump_ = nullptr;
            head_->gap_ = 0;
        } else {
            newNode->gap_ = 1;
        }
        head_ = newNode;
        updateGapsAndJumpPointers();
        return true;
    } else {
        Node* current = head_;
        Node* prev = nullptr;
        while (current != nullptr && current->data_ < s) {
            prev = current;
            current = current->next_;
        }
        newNode->next_ = current;
        prev->next_ = newNode;
        updateGapsAndJumpPointers();
        return true;
    }
}

void JumpList::updateGapsAndJumpPointers() {
    Node* jumpNode = head_;
    while (jumpNode != nullptr) {
        int count = 1;
        Node* current = jumpNode->next_;
        while (current != nullptr && current != jumpNode->jump_) {
            count++;
            current = current->next_;
        }
        jumpNode->gap_ = count;
        if (count > MAX_GAP_SIZE) {
            int splitPoint = (count + 1) / 2;
            Node* secondSegment = jumpNode;
            for (int i = 0; i < splitPoint; i++) {
                secondSegment = secondSegment->next_;
            }
            jumpNode->jump_ = secondSegment;
            jumpNode->gap_ = splitPoint;
            secondSegment->jump_ = nullptr;
            secondSegment->gap_ = count - splitPoint;
        }
        jumpNode = jumpNode->jump_;
    }
}


bool JumpList::erase(const string& s) {
	Node* current = head_;
    Node* prev = nullptr;

    // Search for the node
    while (current != nullptr && current->data_ != s) {
        prev = current;
        current = current->next_;
    }

    if (current == nullptr) return false;  // Node not found

    // If the node to be deleted is the head node
    if (prev == nullptr) {
        head_ = head_->next_;
        delete current;

        // Handle jump pointer and gap updates after deleting head node
        if (head_ != nullptr) {
            //head_->gap_ = (head_->next_ != nullptr) ? 1 : 0;  // New head node's gap
            updateGapsAndJumpPointers();  // Adjust gaps and jump pointers after deletion
        }
        return true;
    }

    // Regular node deletion (non-head node)
    prev->next_ = current->next_;
    delete current;

    if (prev->gap_ == 1 || prev->jump_ == current) {
        updateGapsAndJumpPointers();
    }
    return true;
}