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


struct Node{
    public:
        int value;
        Node*next;
        Node(int v):value(v),next(nullptr){}
};

//template<typename T>
class SingleLinkedList{
    public:

        Node*head;
        int size=0; 
        SingleLinkedList(){
            
        }
        void Init(){//初始化链表即为定义链表头，同时作为虚拟头结点,复杂度为O(1)
           
            head=new Node(0);

            head->next=nullptr;
            size=0;
        }
        void Insert(int value,int index){
            
            if(index>size||index<0){
                
                cout<<"Invalid index"<<endl;

                return;
            }
            Node * newNode=new Node(value);
            Node* cur=head;
            for(int i=0;i<index&&cur!=nullptr;i++){
                cur=cur->next;
                
            }
         
            newNode->next=cur->next;//将新节点的next指向head的next,复杂度为O(1),要注意先后顺序，
            //不能先将head的next指向newNode,否则会丢失head的next
            cur->next=newNode;
            ++size;
        }
        void Remove(int index){
            if(index>=size||index<0){

                cout<<"Invalid index to remove"<<endl;
                return;
            }
            Node * temp=head;
            for(int i=0;i<index;i++){
                temp=temp->next;
            }
            Node* removeNode=temp->next;
            
            temp->next=removeNode->next;
            delete removeNode;

            
            --size;
        }
        void Find(int value){
            Node* cur=head->next;
            int index=0;
            bool found=false;
            while(cur!=nullptr){
                if(cur->value==value){
                    found=true;

                    cout<<"Found at index "<<index<<endl;
                   
                }
                cur=cur->next;
                index++;
            }
            if(!found)
            cout<<"Not found"<<endl;
        }//查找元素value,并输出其所有的下标,如果不存在则输出"Not found",复杂度为O(n)
        void Update(int value,int index){
            Node* cur=head->next;
            for(int i=0;i<index;i++){
                cur=cur->next;
            }
            if(cur==nullptr||index<0){
                cout<<"Invalid index"<<endl;
                return;
            }
            cur->value=value;
        }//更新指定位置的元素,复杂度为O(n)

};
class dNode{
    public:
        int value;
        dNode*next;
        dNode*prev;
        dNode(int value):value(value),next(nullptr),prev(nullptr){}
};
class DoubleLinkedList{
    public:
        dNode*head;
        dNode* tail;
        int size=0;
    
        DoubleLinkedList():head(nullptr){}
        void Init(){//初始化链表即为定义链表头，同时作为虚拟头结点,复杂度为O(1)
            
            head=new dNode(0);
            head->next=nullptr;
            head->prev=nullptr;
            tail=head;
            size=0;
        }
        void Insert(int value,int index){//在指定位置插入元素,只需改变指针指向，复杂度为O(n)，但是远快于数组，因为数组需要移动元素
         if(index>size||index<0){
                
                cout<<"Invalid index"<<endl;
                return;
            }
            dNode * newNode=new dNode(value);
            dNode* cur=head;
            for(int i=0;i<index;i++){
                cur=cur->next;
            }
           
            newNode->next=cur->next;//将新节点的next指向head的next,复杂度为O(1),要注意先后顺序，
            //不能先将head的next指向newNode,否则会丢失head的next
            cur->next=newNode;
            newNode->prev=cur;
            ++size;

        }
        void Remove(int index)
        {
            dNode * temp=head;
            for(int i=0;i<index;i++){
                temp=temp->next;
            }
            if(temp==nullptr||index<0){
                cout<<"Invalid index"<<endl;
                return;
            }
            temp->next=temp->next->next;
            temp->next->prev=temp;
            --size;
        }
        void Find(int value)
        {
            dNode* cur=head->next;
            int index=0;
            bool found=false;
            while(cur!=nullptr){
                if(cur->value==value){
                    found=true;

                    cout<<"Found at index "<<index<<endl;

                }
                cur=cur->next;
                index++;
            }
            if(!found)
            cout<<"Not found"<<endl;
        }//查找元素value,并输出其所有的下标,如果不存在则输出"Not found",复杂度为O(n)
        void Update(int value,int index)
        {
            dNode* cur=head->next;
            for(int i=0;i<index;i++){
                cur=cur->next;
            }
            if(cur==nullptr||index<0){
                cout<<"Invalid index"<<endl;
                return;
            }
            cur->value=value;
        }//更新指定位置的元素,复杂度为O(n)



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
    SingleLinkedList list;
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
    Node* cur=list.head->next;
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
    DoubleLinkedList list;
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
    dNode* cur=list.head->next;
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
