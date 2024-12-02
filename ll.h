#pragma once

#include"CommonHeaders.h"



template <typename T>
class Array{
    private:
        vector<T> arr;
    public:
        Array(){}
        Array(int length){
            arr.resize(length);
        }
        T& operator[](int index){
            return arr[index];
        }
        int getSize(){
            return arr.size();
        }
        vector<T>& getarr(){
            return arr;
        }
        void Init(){
            for(int i=0;i<arr.size();i++){
                arr[i]=0;
            }
        }
        void Insert(T value,int index){
            arr.insert(arr.begin()+index,value);//在指定位置插入元素 ,并将后面的元素后移一位,复杂度为O(n)

        }
        void Remove(int index){
            arr.erase(arr.begin()+index);//删除指定位置的元素,并将后面的元素前移一位，复杂度为O(n)
        }
        void Find(T value)//查找元素value,并输出其下标,如果不存在则输出"Not found",复杂度为O(n)

        {
            bool found=false;

            for(int i=0;i<arr.size();i++){
                if(arr[i]==value){
                    found=true;
                    cout<<"Found at index "<<i<<endl;
                }
            }
            if(!found)
            cout<<"Not found"<<endl;
        }
        void Update(T value,int index){//更新指定位置的元素,复杂度为O(1)
            arr[index]=value;
        }
 
};


template<typename T>
struct Node{
    public:
        T value;
        Node<T>* next;
        Node(T v): value(v), next(nullptr) {}
};

template<typename T>
class SingleLinkedList{
    public:
        Node<T>* head;
        int size = 0; 
        SingleLinkedList() : head(nullptr) {}

        void Init() { // 初始化链表即为定义链表头，同时作为虚拟头结点,复杂度为O(1)
            head = new Node<T>(T());
            head->next = nullptr;
            size = 0;
        }
        
        void Insert(T value, int index=-114514) {
            if(index == -114514)
                index = size;
            if(index > size || index < 0) {
                cout << "Invalid index" << endl;
                return;
            }
            Node<T>* newNode = new Node<T>(value);
            Node<T>* cur = head;
            for(int i = 0; i < index && cur != nullptr; i++) {
                cur = cur->next;
            }
            newNode->next = cur->next;
            cur->next = newNode;
            ++size;
        }

        void Remove(int index) {
            if(index >= size || index < 0) {
                cout << "Invalid index to remove" << endl;
                return;
            }
            Node<T>* temp = head;
            for(int i = 0; i < index; i++) {
                temp = temp->next;
            }
            Node<T>* removeNode = temp->next;
            temp->next = removeNode->next;
            delete removeNode;
            --size;
        }

        void Find(T value) {
            Node<T>* cur = head->next;
            int index = 0;
            bool found = false;
            while(cur != nullptr) {
                if(cur->value == value) {
                    found = true;
                    cout << "Found at index " << index << endl;
                }
                cur = cur->next;
                index++;
            }
            if(!found)
                cout << "Not found" << endl;
        }

        void Update(T value, int index) {
            if(index < 0 || index >= size) {
                cout << "Invalid index" << endl;
                return;
            }
            Node<T>* cur = head->next;
            for(int i = 0; i < index; i++) {
                cur = cur->next;
            }
            cur->value = value;
        }
};

template<typename T>
class dNode{
    public:
        T value;
        dNode<T>* next;
        dNode<T>* prev;
        dNode(T v): value(v), next(nullptr), prev(nullptr) {}
};

template<typename T>
class DoubleLinkedList{
    public:
        dNode<T>* head;
        dNode<T>* tail;
        int size = 0;

        DoubleLinkedList() : head(nullptr), tail(nullptr) {}

        void Init() { // 初始化链表即为定义链表头，同时作为虚拟头结点,复杂度为O(1)
            head = new dNode<T>(T());
            head->next = nullptr;
            head->prev = nullptr;
            tail = head;
            size = 0;
        }

        void Insert(T value, int index) { // 在指定位置插入元素
            if(index > size || index < 0) {
                cout << "Invalid index" << endl;
                return;
            }
            dNode<T>* newNode = new dNode<T>(value);
            dNode<T>* cur = head;
            for(int i = 0; i < index; i++) {
                cur = cur->next;
            }
            newNode->next = cur->next;
            if(cur->next != nullptr)
                cur->next->prev = newNode;
            cur->next = newNode;
            newNode->prev = cur;
            if(newNode->next == nullptr)
                tail = newNode;
            ++size;
        }

        void Remove(int index) {
            if(index < 0 || index >= size) {
                cout << "Invalid index" << endl;
                return;
            }
            dNode<T>* temp = head;
            for(int i = 0; i < index; i++) {
                temp = temp->next;
            }
            dNode<T>* removeNode = temp->next;
            temp->next = removeNode->next;
            if(removeNode->next != nullptr)
                removeNode->next->prev = temp;
            else
                tail = temp;
            delete removeNode;
            --size;
        }

        void Find(T value) {
            dNode<T>* cur = head->next;
            int index = 0;
            bool found = false;
            while(cur != nullptr) {
                if(cur->value == value) {
                    found = true;
                    cout << "Found at index " << index << endl;
                }
                cur = cur->next;
                index++;
            }
            if(!found)
                cout << "Not found" << endl;
        }

        void Update(T value, int index) {
            if(index < 0 || index >= size) {
                cout << "Invalid index" << endl;
                return;
            }
            dNode<T>* cur = head->next;
            for(int i = 0; i < index; i++) {
                cur = cur->next;
            }
            cur->value = value;
        }
};
void testArray(){
    Array<int> arr(10);
    arr.Init();
    arr.Insert(1,0);
    arr.Insert(2,1);
    arr.Insert(3,2);
    arr.Insert(4,3);
    arr.Insert(5,4);
    arr.Insert(6,5);
    arr.Insert(7,6);
    arr.Insert(8,7);
    cout<<"Initial array:"<<endl;
    for(int i=0;i<arr.getSize();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    arr.Remove(2);
    cout<<"After remove 2:"<<endl;
    for(int i=0;i<arr.getSize();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<"look for 3 in the list:"<<endl;
    arr.Find(3);
    arr.Update(10,3);
    cout<<"After update 3 to 10:"<<endl;
    for(int i=0;i<arr.getSize();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;


}
void testSingleLinkedList(){
    SingleLinkedList<int>  list;
    list.Init();
    list.Insert(1,0);
    list.Insert(2,1);
    list.Insert(3,2);
    list.Insert(4,3);
    list.Insert(5,4);
    list.Insert(6,5);
    list.Insert(7,6);
    list.Insert(8,7);
    cout<<"Initial list:"<<endl;
    Node<int>* cur=list.head->next;
    while(cur!=nullptr){
        
        cout<<cur->value<<" ";
        cur=cur->next;
    }
    cout<<endl;
    list.Remove(2);
    cout<<"After remove 2:"<<endl;
    cur=list.head->next;
    while(cur!=nullptr){
        cout<<cur->value<<" ";
        cur=cur->next;
    }
    cout<<endl;
    cout<<"look for 4 in the list:"<<endl;
    list.Find(4);
    list.Update(10,3);
    cout<<"After update 3 to 10:"<<endl;
    cur=list.head->next;
    while(cur!=nullptr){
        cout<<cur->value<<" ";
        cur=cur->next;
    }
    cout<<endl;

    
}
void testDoubleLinkedList(){
    DoubleLinkedList<int> list;
    list.Init();
    list.Insert(1,0);
    list.Insert(2,1);
    list.Insert(3,2);
    list.Insert(4,3);
    list.Insert(5,4);
    list.Insert(6,5);
    list.Insert(7,6);
    list.Insert(8,7);
    cout<<"Initial double-linked list:"<<endl;
    dNode<int>* cur=list.head->next;
    while(cur!=nullptr){
        cout<<cur->value<<" ";
        cur=cur->next;
    }
    cout<<endl;
    list.Remove(2);
    cout<<"After remove 2:"<<endl;
    cur=list.head->next;
    while(cur!=nullptr){
        cout<<cur->value<<" ";
        cur=cur->next;
    }   
    cout<<endl;
    cout<<"look for 7 in the list:"<<endl;
    list.Find(7);
    list.Update(10,3);
    cout<<"After update 3 to 10:"<<endl;
    cur=list.head->next;
    while(cur!=nullptr){
        cout<<cur->value<<" ";
        cur=cur->next;
    }
    cout<<endl;
}
