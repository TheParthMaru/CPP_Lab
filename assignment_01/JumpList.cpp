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
    Node *current = head_;
    while (current != nullptr)
    {
        Node *next = current->next_;
        delete current; // Delete the current node
        current = next; // Move to the next node
    }
}

int JumpList::size() const
{
    int size = 0;

    Node *currentNode = head_;

    while (currentNode != nullptr)
    {
        ++size;
        currentNode = currentNode->next_;
    }
    // Added just for debugging
    // cout << "Size: " << counter << endl;
    return size; // dummy
}

// DONE FOR YOU, DO NOT CHANGE
bool JumpList::find(const string &s) const
{
    // Added just for debugging
    // cout << "Inside find()" << endl;
    if (head_ == nullptr)
    {
        // Added just for debugging
        // cout << "Not found" << endl;
        return false;
    }

    // moving along the fast lane
    Node *tmp = head_;
    while (tmp->jump_ != nullptr && tmp->jump_->data_ < s)
    {
        // Added just for debugging
        // cout << "Still searching" << endl;
        tmp = tmp->jump_;
    }

    // tmp now points to the jump node at the start of the segment where s could be

    // now slow lane
    while (tmp != nullptr)
    {

        if (tmp->data_ == s)
        {
            // Added just for debugging
            // cout << "Matched" << endl;
            return true; // match
        }
        else if (tmp->data_ > s)
        {
            // Added just for debugging
            // cout << "Not Matched" << endl;
            return false; // went past without finding s
        }
        else
            tmp = tmp->next_;
    }
    // Added just for debugging
    // cout << "Not Matched" << endl;
    return false; // end of list
}

string JumpList::get(int i) const
{
    // Added just for debugging
    // cout << "Inside get()" << endl;
    if (i < 0 || i > size())
    {
        // Added just for debugging
        // cout << "Not found" << endl;
        return "";
    }

    Node *currentNode = head_;
    int index = 0;

    while (index < i && currentNode != nullptr)
    {
        currentNode = currentNode->next_;
        ++index;
    }

    if (currentNode != nullptr)
    {
        // Added just for debugging
        // cout << "Found" << endl;
        return currentNode->data_;
    }
    else
    {
        // Added just for debugging
        // cout << "Not found" << endl;
        return "";
    }
}

string JumpList::print() const
{
    // If the list is empty, return two empty lines
    if (!head_)
        return "\n\n";

    string result1 = ""; // For the regular list nodes
    string result2 = ""; // For the jump nodes
    string result3 = ""; // For the gaps between jump nodes

    Node *currentNode = head_;
    Node *jumpNode = head_;

    // Line 1: Collect all nodes' data (regular list)
    while (currentNode != nullptr)
    {
        result1 += currentNode->data_ + " ";
        currentNode = currentNode->next_;
    }

    // Remove trailing space from result1
    if (!result1.empty())
    {
        result1.pop_back();
    }

    // Line 2: Collect jump nodes' data
    while (jumpNode != nullptr)
    {
        result2 += jumpNode->data_ + " ";
        if (jumpNode->jump_)
        {
            jumpNode = jumpNode->jump_; // Move to the next jump node
        }
        else
        {
            break; // No more jump nodes
        }
    }

    // Remove trailing space from result2
    if (!result2.empty())
    {
        result2.pop_back();
    }

    // Line 3: Collect gaps between jump nodes
    jumpNode = head_; // Reset to head to capture gap values
    while (jumpNode != nullptr && jumpNode->jump_ != nullptr)
    {
        result3 += to_string(jumpNode->gap_) + " "; // Add the gap value
        jumpNode = jumpNode->jump_;                 // Move to the next jump node
    }

    // After collecting jump nodes, handle the last node's gap
    if (jumpNode != nullptr && jumpNode->jump_ == nullptr) // Last jump node
    {
        result3 += to_string(jumpNode->gap_) + " ";
    }

    // Remove trailing space from result3
    if (!result3.empty())
    {
        result3.pop_back();
    }

    // Return the formatted result with newline-separated lines
    return result1 + "\n" + result2 + "\n" + result3;
}

string JumpList::prettyPrint() const
{
    string result = "";
    Node *current = head_;

    // First, print the regular linked list nodes with " --> "
    while (current != nullptr)
    {
        result += current->data_;

        // Add " --> " if there's a next node
        if (current->next_ != nullptr)
            result += " --> ";

        current = current->next_;
    }

    result += "\n";

    // Now, print the jump nodes in the desired format with the gaps
    current = head_;
    Node *previousJumpNode = nullptr;

    while (current != nullptr)
    {
        if (current->jump_ != nullptr)
        {
            // Print the jump node list on a new line
            result += current->data_;
            Node *jumpNode = current->jump_;
            result += " ---------------------> " + jumpNode->data_;

            int gap = 1;
            Node *tempNode = jumpNode;
            while (tempNode->next_ != nullptr)
            {
                tempNode = tempNode->next_;
                gap++;
                result += " --> " + tempNode->data_;
            }

            result += "\n";
            result += to_string(gap); // Print the gap
        }

        current = current->next_;
    }

    return result;
}

bool JumpList::insert(const string &s)
{
    if (head_ == nullptr)
    {
        head_ = new Node(s, nullptr, nullptr, 1); // Initially set gap_ as 1 (head counts for itself)
        return true;
    }

    Node *currentNode = head_;
    // Move to the correct position for insertion using the jump pointers
    while (currentNode->jump_ != nullptr && currentNode->jump_->data_ < s)
    {
        currentNode = currentNode->jump_;
    }

    Node *prev = nullptr;
    Node *current = currentNode;
    while (current != nullptr && current->data_ < s)
    {
        prev = current;
        current = current->next_;
    }

    // When duplicate is matched, return false
    if (current != nullptr && current->data_ == s)
    {
        return false;
    }

    // Insert the new node in the list
    Node *newNode = new Node(s, current, nullptr, 0);
    if (prev == nullptr)
    {
        head_ = newNode;
    }
    else
    {
        prev->next_ = newNode;
    }

    // Adjust jump nodes and gap values for the new node
    Node *segmentStart = currentNode;
    int segmentSize = 0;
    while (segmentStart != nullptr && segmentSize < MAX_GAP_SIZE + 1)
    {
        segmentStart = segmentStart->next_;
        segmentSize++;
    }

    if (segmentSize > MAX_GAP_SIZE)
    {
        int splitPoint = (segmentSize + 1) / 2;
        Node *splitNode = currentNode;
        for (int i = 1; i < splitPoint; i++)
        {
            splitNode = splitNode->next_;
        }

        currentNode->jump_ = splitNode;
        currentNode->gap_ = splitPoint;

        // Accumulate gap for the new jump node
        splitNode->gap_ = segmentSize - splitPoint;

        // Traverse from the current jump node to adjust gaps
        Node *tempNode = currentNode;
        while (tempNode != nullptr)
        {
            tempNode->gap_ += 1;
            tempNode = tempNode->next_;
        }
    }

    // After the insertion, adjust the gap for the last jump node (if any)
    Node *jumpNode = head_;
    while (jumpNode != nullptr && jumpNode->jump_ != nullptr)
    {
        // Calculate the gap for the last jump node
        if (jumpNode->jump_->next_ == nullptr) // Last jump node
        {
            Node *lastJump = jumpNode->jump_;
            int gapToEnd = 0;
            while (lastJump != nullptr)
            {
                gapToEnd++;
                lastJump = lastJump->next_;
            }
            jumpNode->gap_ = gapToEnd;
        }
        jumpNode = jumpNode->jump_; // Move to the next jump node
    }

    return true;
}

bool JumpList::erase(const string &s)
{
    if (head_ == nullptr)
    {
        return false; // Empty list, nothing to delete
    }

    Node *current = head_;
    Node *prev = nullptr;

    // Locate the node to erase using the "fast lane"
    while (current != nullptr && current->data_ != s)
    {
        prev = current;
        current = current->jump_; // Move via the jump pointer (fast lane)
    }

    // If the node wasn't found, return false
    if (current == nullptr)
    {
        return false;
    }

    // Deleting a non-jump node
    if (current->jump_ == nullptr)
    {
        if (prev == nullptr)
        {
            // If the node is the head, just move the head to the next node
            head_ = current->next_;
        }
        else
        {
            // Adjust the previous node's next_ pointer
            prev->next_ = current->next_;
        }
    }
    else
    {
        // Deleting a jump node - merge the two segments around it
        if (prev == nullptr)
        {
            // If the node is the head, set the next node as the new head
            head_ = current->next_;
            // Ensure the next node becomes a jump node (if not already)
            if (head_ != nullptr && head_->jump_ == nullptr)
            {
                head_->jump_ = head_->next_; // Update jump pointer for the new head
            }
        }
        else
        {
            // Merge the segments around the jump node
            prev->jump_ = current->jump_; // Link the previous segment to the jump segment
        }

        // Adjust gap size if necessary
        if (current->next_ != nullptr && current->next_->jump_ != nullptr)
        {
            current->next_->gap_--;
        }
    }

    // Release the memory of the current node
    delete current;

    // Now adjust jump nodes and potentially split if the new segment is too big
    Node *segmentStart = head_;
    int segmentSize = 0;

    // Traverse to determine the segment size after the removal
    while (segmentStart != nullptr)
    {
        segmentStart = segmentStart->next_;
        segmentSize++;
    }

    // If the segment is too large, split it as needed (split if segmentSize > MAX_GAP_SIZE)
    if (segmentSize > MAX_GAP_SIZE)
    {
        Node *splitNode = head_;
        int splitPoint = segmentSize / 2;

        for (int i = 0; i < splitPoint; i++)
        {
            splitNode = splitNode->next_;
        }

        head_->jump_ = splitNode; // Update the jump pointer
        head_->gap_ = splitPoint;
        splitNode->gap_ = segmentSize - splitPoint;
    }

    return true;
}
