#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

// Print all integers in the list, in order
void print(Node *head) {
    Node *temp = head;

    if (temp == nullptr) {
        cout << "List is empty" << endl;
        return;
    }

    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Find integer t from the list, returning a pointer to that node.
Node* find(Node *head, int t) {
    Node* tmp = head;
    while (tmp != nullptr) {
        if (tmp->data == t) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return nullptr; // Return nullptr if not found
}

// Insert integer t to the list as the new head
void insert_head(Node *&head, int t) {
    Node *tmp = new Node;
    tmp->data = t;
    tmp->next = head;
    head = tmp;
}

// Insert t as a new node after "location"
void insert_after(Node *location, int t) {
    if (location == nullptr) return; 
    Node *newNode = new Node;
    newNode->data = t;
    newNode->next = location->next; 
    location->next = newNode;        
}

// Remove head from the list
void remove_head(Node *&head) {
    if (head == nullptr) return; 
    Node *temp = head;           
    head = head->next;           
    delete temp;                 
}

// Remove the NEXT integer after the one pointed to by "location"
void remove_after(Node *location) {
    if (location == nullptr || location->next == nullptr) return; 
    Node *temp = location->next; 
    location->next = temp->next;  
    delete temp;
}

// Delete all nodes and release all memory
void cleanup(Node *&head) {
    Node *current = head; 
    while (current != nullptr) {
        Node *nextNode = current->next; 
        delete current;                  
        current = nextNode; 
    }
    head = nullptr;
}

int main() {
    Node *mylist = nullptr; // Initializing the linked list to nullptr
    print(mylist);
    insert_head(mylist, 1);
    insert_head(mylist, 2);
    insert_head(mylist, 3);
    print(mylist);

    Node* result = find(mylist, 3);
    if (result != nullptr) insert_after(result, 5);
    print(mylist); 

    remove_head(mylist);
    print(mylist); 

    remove_after(find(mylist, 5));
    print(mylist); 

    cleanup(mylist);
    print(mylist); 

    return 0;
}
