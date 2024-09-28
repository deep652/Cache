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
    void deleteGivenNode(Node **keynode);
    void deleteGivenNode(Node *keynode);
    bool search(Node *node);
};
bool DLL :: search(Node *node)
{
    Node *it = head;
    while(it != node)
    {
        it = it->next;
    }
    if(it -> next == nullptr)
    {
        return false;
    }
    return true;

}
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

  //cout<<"Element at the head is " << head->m_data << endl;
   
}

void DLL:: insertAtEnd(Node **newNode)
{
    if(head == nullptr)

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
        //int get();
        //void put(int data);
        LRU(int s): size{s}{}
        LRU(){}

        void put(int key, int data);
        int get(int key);
};

//TODO deleteGivenNode
void DLL:: deleteGivenNode(Node **keynode)
{
    //Node *temp = nullptr;
    if(head == *keynode)
    {
        cout<<"Deleted node is at head "<<endl;
        //temp = head;
        head = head -> next;
        head -> prev = nullptr;
        //delete temp;
        return ;
    }
    if(tail == *keynode)
    {
        cout<<"Deleted node is at tail "<<endl;
        //temp = tail;
        tail = tail -> prev;
        tail->next = nullptr;
        return ;
    }
    Node *it = head;
    while(it != *keynode)
    {
        it = it->next;
    }
    if(it == nullptr)
    {
        cout<<"Node not found in the list, value searched was "<<(*keynode)->m_data<<endl;
        return ;
    }
        
    
    it ->prev ->next = it -> next ;
    it->next -> prev = it -> prev;

}

void LRU:: put(int key, int data)
{
    //if exists - delete -> insert -> update the value
    //if doesn't exists - check if size reached its limit
    //yes, delete from the list delete from the cache and insert into the map and insert into the list at the first 
    // 4 3 2 1
    // insert 5

    // 

    if(LRU_Cache.find(key) != LRU_Cache.end())//key exits
    {
        cout<<"found the key in the cache, updating the value: "<<endl;
        Node *keyNode = LRU_Cache[key];
        ll.deleteGivenNode(&keyNode);
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
        cout<<"Cache is full, removing the last recently used element from the cache "<<endl;
        Node *node = ll.deleteAtEnd();
        auto it = LRU_Cache.begin();
        while(it->second != node)
        {
            it++;
        }
        LRU_Cache.erase(it);
        node->m_data = data;
        LRU_Cache[key] = node;
        ll.insertAtFirst(&node);
    }
    else
    {
        cout<<"putting into the cache "<<endl;
        Node *newNode = new Node(data);
        LRU_Cache[key] =  newNode;
        ll.insertAtFirst(&newNode);
        // cout<<"list is : "<<endl;
        // ll.print();
    }
    cout<<"inserted the value "<<data<<" into the cache "<<endl;
}

int LRU:: get(int key)
{
    //if key found 
    //reorder the key in the list
        //how to reorder is
        //search the node in the list --> not needed
        //remove the node
        //insert first
    //return the value
    //else
    //return -1

    if(LRU_Cache.find(key) != LRU_Cache.end())
    {
        cout<<"Key exists in the cache, updating the list to make it recently used value "<<endl;
        Node *node = LRU_Cache[key];
        ll.deleteGivenNode(&node);
        ll.insertAtFirst(&node);
        return node -> m_data;
    }
    else
    {
        cout<<"Key doesn't exists in the cache "<<endl;
        return -1;
    }
    cout<<"get operation completed!!"<<endl;
}

int main()
{
    LRU lru(3);
    lru.put(1,10);
    lru.put(2,20);
    lru.put(3,30);
    cout<<lru.get(1)<<endl;
    lru.put(3,30);
    lru.get(2);
    // lru.put(5,50);
    // cout<<lru.get(3)<<endl;
    // cout<<lru.get(4)<<endl;
    // lru.put(6,60);
    // cout<<lru.get(1)<<endl;
    // cout<<lru.get(5)<<endl;

    return 0;

}