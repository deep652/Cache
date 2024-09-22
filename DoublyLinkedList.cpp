#include<iostream>

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

Node * DLL :: deleteAtEnd()
{
    Node *deletednode = tail;
    tail = tail -> prev;
    tail -> next = nullptr;

    return deletednode;
}
int main()
{
    DLL ll;
    for(int i=1; i<10; i++)
    {
        Node *newnode = new Node(i);
        ll.insertAtFirst(&newnode);
    }
    
    ll.print();

    Node *lastnode = ll.deleteAtEnd();
    cout<<"Last deleted node = "<< lastnode->m_data<<endl;

    cout<<"List: "<<endl;
    ll.print();

    //insert the deleted node at the first of the list
    ll.insertAtFirst(&lastnode);

    cout<<"List: "<<endl;
    ll.print();




}
