#include "JumpList.h"
#include <stdexcept>

Node::Node(const string &s, Node *next, Node *jump, int gap)
{
    // IMPLEMENT ME
}

Node::~Node()
{
    // IMPLEMENT ME
}

JumpList::JumpList()
{
    // IMPLEMENT ME
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
    // IMPLEMENT ME

    return -1; // dummy
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
    // IMPLEMENT ME

    return "nah"; // dummy
}

string JumpList::prettyPrint() const
{
    // IMPLEMENT ME

    return "nah"; // dummy
}

bool JumpList::insert(const string &s)
{
    // IMPLEMENT ME

    return false; // dummy
}

bool JumpList::erase(const string &s)
{
    // IMPLEMENT ME

    return false; // dummy
}