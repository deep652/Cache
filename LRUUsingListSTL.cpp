#include<iostream>
#include<list>
#include<map>

class Node
{
    public:
    int data;
    Node *next;
    Node *prev;
    Node(int value): data(value){}
};
using namespace std;
class LRU
{
    public:
    list<Node *> ll;
    map<int, Node *> cache;
    int size = 3;
    void put(int key, int value);
    int get(int key);
};
void LRU:: put(int key, int value)
{
    //if key exits
    if(cache.find(key) != cache.end())
    {
        cache[key]->data = value;
        //tail
        if(ll.front() == cache[key])
        {
            ll.pop_front();
            cache[key]->data = value;
            ll.push_back(cache[key]);
            return;
        }
        if(ll.back() == cache[key])
        {
            cache[key]->data = value;
            return;
        }
        Node *node = cache[key];
        node->prev->next = node->next;
        node->next->prev = node->prev;
        ll.push_back(node);
    }
    Node *node = new Node(value);
    if(cache.size() > 3)
    {
        Node *leastUsedNode = ll.front();
        ll.pop_front();
        cache.erase(key);
        return;
    }
    cache[key] = node;
    ll.push_back(node);
}
int LRU:: get(int key)
{
    if(cache.size() == 0)
    {
        cout<<"cache is empty!! "<<endl;
        return -1; 
    }
    if(cache.find(key) == cache.end())
    {
        cout<<"key doesn't exits in cache"<<endl;
        return -1;
    }
        //front
        if(ll.front() == cache[key])
        {
            ll.pop_front();
            ll.push_back(cache[key]);
            return cache[key]->data;
        }
        //tail
        if(ll.back() == cache[key])
        {
            return cache[key]->data;
        }
        //given node
        Node *node = cache[key];
        node->prev->next = node->next;
        node->next->prev = node->prev;
        ll.push_back(node);
    return node->data;
}

int main()
{
    LRU ll;
    ll.put(1, 1);
    ll.put(2, 2);
    ll.put(3, 3);
    ll.put(1, 4);
    //for(int i=1; i<4; i++)
    //std::cout<<i<<ll.cache[i]->data<<endl;

    cout<<ll.get(2)<<endl;
    for(int i=1; i<4; i++)
    std::cout<<i<<ll.cache[i]->data<<endl;

    return 0;
}