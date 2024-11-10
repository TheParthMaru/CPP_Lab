#include "JumpList.h"
#include <stdexcept>
#include <iostream>
using namespace std;

// This is a constructor
Node::Node(const string &s, Node *next, Node *jump, int gap)
{
    data_ = s;
    next_ = next;
    jump_ = jump;
    gap_ = gap;
}

Node::~Node()
{
    // IMPLEMENT ME
}

// This will be the default constructor for the JumpList.
// We know that the head will always be a jump node.
JumpList::JumpList()
{
    head_ = nullptr;
}

// DO NOT CHANGE
// You do not need to understand the code here to complete the assignment
JumpList::JumpList(int size, const string *arr)
{

    const string s[] = {"a", "b", "blah", "c", "cat", "d", "etc", "ooo...", "x", "zzz"};
    const string *sp = (arr == nullptr) ? s : arr;

    Node **npp = new Node *[size];
    npp[size - 1] = new Node(sp[size - 1], nullptr, nullptr, 0);
    for (int i = size - 2; i >= 0; i--)
        npp[i] = new Node(sp[i], npp[i + 1], nullptr, 0);

    if (arr == nullptr)
    {

        if (size == 1)
            npp[0]->gap_ = 1;
        else if (size == 3)
            npp[0]->gap_ = 3;
        else if (size == 10)
        {
            npp[0]->jump_ = npp[5];
            npp[5]->jump_ = npp[8];
            npp[0]->gap_ = 5;
            npp[5]->gap_ = 3;
            npp[8]->gap_ = 2;
        }
        else
            throw std::invalid_argument("size must be 1, 3 or 10");
    }
    else
    {

        // jump node every MAX_GAP_SIZE
        int i;
        for (i = 0; i < size - MAX_GAP_SIZE; i += MAX_GAP_SIZE)
        {
            npp[i]->jump_ = npp[i + MAX_GAP_SIZE];
            npp[i]->gap_ = MAX_GAP_SIZE;
        }
        npp[i]->gap_ = size % MAX_GAP_SIZE;
        if (npp[i]->gap_ == 0)
            npp[i]->gap_ = MAX_GAP_SIZE; // 0 need to become 5!
    }

    head_ = npp[0];
    delete[] npp; // note that the local array npp gets destroyed here but the nodes stay alive!
}

JumpList::~JumpList()
{
    // IMPLEMENT ME
}

int JumpList::size() const
{
    int counter = 0;

    Node *currentNode = head_;

    while (currentNode != nullptr)
    {
        ++counter;
        currentNode = currentNode->next_;
    }

    return counter; // dummy
}

// DONE FOR YOU, DO NOT CHANGE
bool JumpList::find(const string &s) const
{

    if (head_ == nullptr)
        return false;

    // moving along the fast lane
    Node *tmp = head_;
    while (tmp->jump_ != nullptr && tmp->jump_->data_ < s)
        tmp = tmp->jump_;

    // tmp now points to the jump node at the start of the segment where s could be

    // now slow lane
    while (tmp != nullptr)
    {

        if (tmp->data_ == s)
            return true; // match
        else if (tmp->data_ > s)
            return false; // went past without finding s
        else
            tmp = tmp->next_;
    }

    return false; // end of list
}

string JumpList::get(int i) const
{
    // IMPLEMENT ME

    return "nah"; // dummy
}

string JumpList::print() const
{
    string result = "";
    Node *currentNode = head_;

    while (currentNode != nullptr)
    {
        result += currentNode->data_ + " ";
        currentNode = currentNode->next_;
    }

    return result;
}

string JumpList::prettyPrint() const
{
    // IMPLEMENT ME

    return "nah"; // dummy
}

bool JumpList::insert(const string &s)
{
    Node *newNode = new Node(s, nullptr, nullptr, 0);

    // If empty list, then we need to insert at head.
    if (head_ == nullptr)
    {
        head_ = newNode;
        std::cout << "Data: " << s << " inserted" << std::endl;
        return true; // Because we were able to add.
    }

    // Checking if the new node data needs to be added at the beginning
    // Based on the lexicographical order

    if (head_->data_ > s)
    {
        newNode->next_ = head_;
        head_ = newNode;
        cout << "Data: " << s << " inserted" << "\n";
        return true;
    }

    // Finding the correct position for string data lexicographically
    Node *currentNode = head_;
    while (currentNode->next_ != nullptr && currentNode->next_->data_ < s)
    {
        currentNode = currentNode->next_;
    }
    newNode->next_ = currentNode->next_;
    currentNode->next_ = newNode;
    cout << "Data: " << s << " inserted" << "\n";

    return false; // dummy
}

bool JumpList::erase(const string &s)
{
    // IMPLEMENT ME

    return false; // dummy
}