#include<iostream>
#include <map>

using namespace std;
class Node
{
    public:
        int m_data;
        Node *next;
        Node *prev;

        Node(int data):m_data{data}, next{nullptr}, prev{nullptr}{}
};

class DLL
{
    public:
    Node *head = nullptr, *tail = nullptr;
    void insertAtFirst(Node **newnode);
    Node * deleteAtEnd();
    void print();
    void insertAtEnd(Node **newNode);
    void deleteGivenNode(Node *keynode);
};
void DLL :: print()
{
    Node *it =  head;

    while(it != nullptr)
    {
        cout<<it->m_data<<"\t";
        it = it -> next;
    }
    cout<<"\n";
}
void DLL:: insertAtFirst(Node **newnode)
{
    // 1 2 3
    /*
    head -> 1
    insert 5
    head -> 5 
    list 5 1 2 3
    */

   if(head == nullptr)
   {
        head = *newnode;
        tail = *newnode;
   }
   else
   {
        (*newnode)->next = head;
        head -> prev = *newnode;
        head = *newnode;
   }

  // cout<<"Element at the head is " << head->m_data << endl;
   
}

void DLL:: insertAtEnd(Node **newNode)
{
    (*newNode)->prev = tail;
    tail->next = *newNode;
    tail = *newNode;
}


Node * DLL :: deleteAtEnd()
{
    Node *deletednode = tail;
    tail = tail -> prev;
    tail -> next = nullptr;

    return deletednode;
}

class LRU
{
    private:
        int size;
        map<int, Node *> LRU_Cache;
        DLL ll;

    public:
        int get();
        //void put(int data);
        LRU(int s): size{s}{}

        void put(int key, int data);
};

//TODO deleteGivenNode
void DLL:: deleteGivenNode(Node *keynode)
{
    //Node *temp = nullptr;
    if(head == keynode)
    {
        //temp = head;
        head = head -> next;
        head -> prev = nullptr;
        //delete temp;
        return ;
    }
    if(tail == keynode)
    {
        //temp = tail;
        tail = tail -> prev;
        tail->next = nullptr;
    }
    Node *it = head;
    while(it != keynode)
    {
        it = it->next;
    }
    if(it == nullptr)
        return ;
    
    it ->prev ->next = it -> next ;
    it->next -> prev = it -> prev;

}

void LRU:: put(int key, int data)
{
    //if exists - delete -> insert -> update the value
    //if doesn't exists - returns -1

    if(LRU_Cache.find(key) != LRU_Cache.end())//key exits
    {
        Node *keyNode = LRU_Cache[key];
        ll.deleteGivenNode(keyNode);
        keyNode->m_data = data;
        ll.insertAtFirst(&keyNode);
    }
    else if (LRU_Cache.size() == size)
    {
        //delete last node
        //remove the key from map
        //create new node wtth the key
        //insert at first
        //update the map
        
    }
    else
    {
        Node *newNode = new Node(data);
        LRU_Cache[key] =  newNode;
        ll.insertAtEnd(&newNode);
    }
}

int main()
{
    return 0;
}