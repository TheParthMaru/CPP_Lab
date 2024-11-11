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
    // Case 1: If the list is empty, directly insert the first node.
    if (head_ == nullptr)
    {
        head_ = new Node(s, nullptr, nullptr, 1); // First node, gap is 1 as it's the only node
        return true;
    }

    // Case 2: Traverse using the jump pointers to find the correct segment for insertion.
    Node *currentNode = head_;
    while (currentNode->jump_ != nullptr && currentNode->jump_->data_ < s)
    {
        currentNode = currentNode->jump_;
    }

    // Case 3: Traverse within the current segment to find the correct position.
    Node *prev = nullptr;
    Node *current = currentNode;
    while (current != nullptr && current->data_ < s)
    {
        prev = current;
        current = current->next_;
    }

    // Case 4: If the element already exists, return false.
    if (current != nullptr && current->data_ == s)
    {
        return false; // Duplicate found, no insertion.
    }

    // Case 5: Insert the new node.
    Node *newNode = new Node(s, current, nullptr, 0); // New node with no jump node initially.
    if (prev == nullptr)
    {
        head_ = newNode; // Insert at the beginning of the list.
    }
    else
    {
        prev->next_ = newNode; // Insert in the middle or end of the list.
    }

    // Case 6: Update jump nodes and gaps.
    // Find the segment where the new node is inserted.
    Node *segmentStart = head_;
    int segmentSize = 0;
    while (segmentStart != nullptr && segmentSize < MAX_GAP_SIZE + 1)
    {
        segmentStart = segmentStart->next_;
        segmentSize++;
    }

    // If the segment exceeds MAX_GAP_SIZE, split the segment.
    if (segmentSize > MAX_GAP_SIZE)
    {
        int splitPoint = (segmentSize + 1) / 2;
        Node *splitNode = head_;
        for (int i = 1; i < splitPoint; i++)
        {
            splitNode = splitNode->next_;
        }

        // Update the jump and gap values for the new split segment.
        currentNode->jump_ = splitNode;
        currentNode->gap_ = splitPoint;

        splitNode->gap_ = segmentSize - splitPoint;

        // Traverse from the current jump node to adjust gaps.
        Node *tempNode = currentNode;
        while (tempNode != nullptr)
        {
            tempNode->gap_ += 1;
            tempNode = tempNode->next_;
        }
    }

    // Case 7: After insertion, adjust the gap for the last jump node (if any).
    Node *jumpNode = head_;
    while (jumpNode != nullptr && jumpNode->jump_ != nullptr)
    {
        if (jumpNode->jump_->next_ == nullptr) // Last jump node, calculate the gap to the end.
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
        jumpNode = jumpNode->jump_; // Move to the next jump node.
    }

    return true; // Insertion successful.
}

bool JumpList::erase(const string &s)
{
    if (head_ == nullptr) // If the list is empty, nothing to erase
        return false;

    // Case 1: If the node to erase is at the head
    if (head_->data_ == s)
    {
        Node *temp = head_;
        head_ = head_->next_; // Move the head to the next node
        delete temp;          // Free the memory of the erased node

        // After removing the head, we need to adjust the jump nodes if necessary
        if (head_ != nullptr) // Check if there's a new head to adjust jump node
        {
            // If the new head is not already a jump node, we need to make it one
            if (head_->jump_ == nullptr)
            {
                head_->jump_ = head_; // For a single element, point jump to itself
                head_->gap_ = 1;      // Set gap to 1 (head node counts for itself)
            }
        }

        return true;
    }

    // Case 2: Traverse the list to find the node to erase
    Node *prev = nullptr;
    Node *current = head_;
    while (current != nullptr && current->data_ != s)
    {
        prev = current;
        current = current->next_;
    }

    // Case 3: If the node is not found, return false
    if (current == nullptr)
    {
        return false; // Element not found
    }

    // Case 4: If the node is found, remove it
    prev->next_ = current->next_; // Bypass the node to be deleted
    delete current;               // Free the memory of the erased node

    // Adjust the jump nodes if necessary
    Node *jumpNode = head_;
    while (jumpNode != nullptr && jumpNode->jump_ != nullptr)
    {
        // Check if we need to adjust the gap size of the jump node
        Node *currentSegment = jumpNode;
        int segmentSize = 0;
        while (currentSegment != nullptr && segmentSize < MAX_GAP_SIZE)
        {
            currentSegment = currentSegment->next_;
            segmentSize++;
        }

        if (segmentSize > MAX_GAP_SIZE)
        {
            // If the segment is too big, split it by adjusting the jump node
            Node *splitNode = jumpNode;
            for (int i = 1; i < segmentSize / 2; i++)
            {
                splitNode = splitNode->next_;
            }

            jumpNode->jump_ = splitNode;
            jumpNode->gap_ = segmentSize / 2;
            splitNode->gap_ = segmentSize - (segmentSize / 2);
        }

        jumpNode = jumpNode->jump_; // Move to the next jump node
    }

    return true;
}
