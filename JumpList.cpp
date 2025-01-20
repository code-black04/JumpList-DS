#include "JumpList.h"
#include <stdexcept>
#include <iostream>
#include <string>
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
if (npp[i]->gap_ == 0) npp[i]->gap_ = MAX_GAP_SIZE;
// 0 need to become 5!
}
head_ = npp[0];
delete [] npp;
// note that the local array npp gets destroyed here but the nodes stay alive!
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
count += current->gap_;// Use jump pointer to skip nodes and speed up traversal
if (current->jump_ != nullptr) {
current = current->jump_;
}// If no jump pointer, move to the next node in sequence
else {
current = current->next_;
}
}
return count;
}
// DONE FOR YOU, DO NOT CHANGE
bool JumpList::find(const string& s) const {
if (head_ == nullptr) return false;
// moving along the fast lane
Node* tmp = head_;
while(tmp->jump_ != nullptr && tmp->jump_->data_ < s)
tmp = tmp->jump_;
// tmp now points to the jump node at the start of the segment where s could be
// now slow lane
while(tmp != nullptr) {
if (tmp->data_ == s) return true;
// match
else if (tmp->data_ > s) return false;
// went past without finding s
else tmp = tmp->next_;
}
return false;
// end of list
}
string JumpList::get(int i) const {
// Check if the index is valid; if so, return an empty string
if (i < 0 || i >= this->size()) return "";
Node* current = head_;
int count = 0;
// Traverse the list, using jumps when possible
while (current != nullptr) {// If index is within the current node's gap range, use next pointers
if (count + current->gap_ > i) {
while (current != nullptr && count < i) {
current = current->next_;
count++;
}
return (current != nullptr) ? current->data_ : "";
}// Otherwise, move to the next jump node and update count
count += current->gap_;
current = current->jump_;
}
return "";
}
string JumpList::print() const {
if (head_ == nullptr) {
return "\n\n";
}
string allDataStr = "";
string jumpNodesStr = "";
string gapsStr = "";
Node* current = head_;
Node* jumpNode = head_;
// Traverse all nodes to build a string of their data
while (current != nullptr) {
allDataStr += current->data_;
current = current->next_;
if (current != nullptr) {
allDataStr += " ";
}
}
// Traverse again to build strings for jump nodes and their gaps
current = head_;
while (current != nullptr) {
if (current == jumpNode) {
jumpNodesStr += current->data_;
gapsStr += std::to_string(current->gap_);// Move to next jump node
jumpNode = jumpNode->jump_;
if (jumpNode != nullptr) {
jumpNodesStr += " ";
gapsStr += " ";
}
}
current = current->next_;
}
// Return concatenated string with all nodes, jump nodes, and gaps
return allDataStr + "\n" + jumpNodesStr + "\n" + gapsStr;
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
// Construct allData and arrows strings with appropriate separators
while (current != nullptr && current->next_ != nullptr) {
allData += current->data_;
allData += " --> ";
current = current->next_;
}
allData += current->data_;
// Add the last node's data without an arrow
// Construct jumpArrows and gapSizes, aligning them with allData and arrows
current = head_;
while (current != nullptr) {
string dataStr = current->data_;
// If current node is a jump node
if (current == jumpNode) {
jumpArrows += dataStr;
// Start jump arrow with the jumpNode's data
size_t jumpLength = 0;
Node* temp = current;
// Calculate the span of the jump arrow to the target jump node, without extra spaces
while (temp != jumpNode->jump_ && temp != nullptr) {
jumpLength += temp->data_.length();
// Only count the data length
if (temp->next_ != nullptr && temp != jumpNode->jump_) {
jumpLength += 5;
// Account for " --> " only between nodes
}
temp = temp->next_;
}
// Fill the remaining part of the jump arrow with "-"
if (jumpNode ->jump_ != nullptr) {
jumpArrows += " " + string(jumpLength - dataStr.length()-3, '-') + "> ";
}
jumpNode = jumpNode->jump_;
// Move to the next jump node
// Align gapSizes with the start of the jump
gapSizes += to_string(current->gap_);
if (current->jump_!=nullptr)
{
gapSizes += string(jumpLength - to_string(current->gap_).length(), ' ');
// Align gap size under jump arrow
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
//check if "s" is present in JumpList do nothing
if (find(s)) return false;
Node* newNode = new Node(s, nullptr, nullptr, 0);
// if list empty, set newNode as head, with it's gap value as 1
if (this->size() == 0) {
head_ = newNode;
head_->gap_ = 1;
return true;
}
Node* jumpNode = head_;
//new value less than current head data
if (head_->data_ > s) {//set head to newNode
newNode->next_ = head_;
newNode->jump_ = head_->jump_;
newNode->gap_ = head_->gap_;
head_ = newNode;//update previous head as non-jump node
newNode->next_->jump_ = nullptr;
newNode->next_->gap_ = 0;
jumpNode = newNode;// increment gap for jump changed
jumpNode->gap_ += 1;
} else {
// insert after head
Node* afterNodeToInsert = head_;
// get jump node having value less than new value
while (afterNodeToInsert->jump_ != nullptr && afterNodeToInsert->jump_->data_ < s) {
jumpNode = afterNodeToInsert->jump_;
afterNodeToInsert = afterNodeToInsert->jump_;
}// find node to insert after
while (afterNodeToInsert->next_ != nullptr && afterNodeToInsert->next_->data_ < s){
afterNodeToInsert = afterNodeToInsert->next_;
}
// if next node is same do not insert
if (afterNodeToInsert->next_ != nullptr && afterNodeToInsert->next_->data_ == s){
return false;
}
Node* newNodeNext = afterNodeToInsert->next_;
afterNodeToInsert->next_ = newNode;
newNode->next_ = newNodeNext;// increment gap for jump changed
jumpNode->gap_ += 1;
}
splitJumpIfMaxGapExceed(jumpNode);
return true;
}
void JumpList::splitJumpIfMaxGapExceed(Node* jumpNode)
{ //if gap < MAX_GAP_SIZE then do nothing
if (jumpNode->gap_ > MAX_GAP_SIZE)
{
int firstSplit = (jumpNode->gap_ / 2);
int secondSplit = (jumpNode->gap_ / 2);
//if remainder non-zero, then increase firstSplit size by 1
if (jumpNode->gap_ % 2 != 0)
{
firstSplit = (jumpNode->gap_ / 2) + 1;
}
Node *secondJumpNode = jumpNode;
// find second jump node
for (int i = 0; i < firstSplit; i++)
secondJumpNode = secondJumpNode->next_;
// update jumps and gap for firstJumpNode for firstSplit
jumpNode->jump_ = secondJumpNode;
jumpNode->gap_ = firstSplit;
Node *thirdJumpNode = secondJumpNode;
// jump node for second jump
for (int i = 0; i < secondSplit; i++)
thirdJumpNode = thirdJumpNode->next_;
// update jumps and gap for secondJumpNode for secondSplit
secondJumpNode->jump_ = thirdJumpNode;
secondJumpNode->gap_ = secondSplit;
}
}
void JumpList::deleteNode(Node* nodeToDelete, Node* previous, Node* previousJump) {
// Case 1: If the node to delete is the head of the list
if (nodeToDelete == head_) {// Update head to the next node
head_ = nodeToDelete->next_;
if (head_ && head_->gap_ == 0) {
head_->jump_ = nodeToDelete->jump_;
head_->gap_ = nodeToDelete->gap_ - 1;
}
}
// Case 2: If the node to delete is a jump node
else if (nodeToDelete->gap_ != 0) {// Update jump pointers to bypass the deleted node
Node* nextJumpNode = nodeToDelete->jump_;
previousJump->jump_ = nextJumpNode ? nextJumpNode : nullptr;
previousJump->gap_ += nodeToDelete->gap_ - 1;
// Link previous node to the next node, skipping the node to delete
previous->next_ = nodeToDelete->next_;
if (previousJump->gap_ > MAX_GAP_SIZE)
splitJumpIfMaxGapExceed(previousJump);
}
// Case 3: If the node to delete is a regular (non-jump) node
else {// Link previous node to the next node
previous->next_ = nodeToDelete->next_;
// Decrease the gap count of the previous jump node to reflect deletion
previousJump->gap_ -= 1;
}
// Delete the target node and set its pointer to nullptr for safety
delete nodeToDelete;
nodeToDelete = nullptr;
}
void JumpList::findClosestNodes(const string& s, Node*& current, Node*& previous, Node*& previousJump) {
// Traverse the list while there is either a valid jump or next node
// with data less than or equal to the target string `s`.
while ((current->jump_ != nullptr && current->jump_->data_ <= s) ||
(current->next_ != nullptr && current->next_->data_ <= s)) {
// Case 1: Traverse via jump pointers if `jump_` is valid and points to data <= `s`
if (current->jump_ != nullptr && current->jump_->data_ <= s) {
Node* temp = current;
while (temp->next_ != nullptr && temp->next_->data_ < s) {
temp = temp->next_;
}
previousJump = current;
previous = temp;
current = current->jump_;
}// Case 2: Traverse via next pointers if jump is invalid or data is too large
else if (current->next_ != nullptr && current->next_->data_ <= s) {// If the current node is a jump node (gap > 0), update `previousJump`
if (current->gap_ != 0) {
previousJump = current;
}
previous = current;
current = current->next_;
}
}
}
// Implementation of the erase function
bool JumpList::erase(const string& s) {
//if `s` is not present in the list, do nothing
if (!find(s)) return false;
// if only head node is present, then directly delete node
if (this->size() == 1) {
deleteNode(head_, nullptr, nullptr);
return true;
}
Node* current = head_;
Node* previous = head_;
Node* previousJump = head_;
// Use the helper function to find the closest nodes
findClosestNodes(s, current, previous, previousJump);
// Proceed with the deletion logic as in your original function
deleteNode(current, previous, previousJump);
return true;
}