#pragma once
#include "CommonHeaders.h"

template <typename T>
class treeNode{
    public:
        T data;
        treeNode<T>* left;
        treeNode<T>* right;
        treeNode<T>* parent;
        treeNode(const T& value)
            : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
};
template<>
class treeNode<DialogueData> {
public:
    DialogueData data;
    treeNode* left;
    treeNode* right;

    treeNode(const DialogueData& value) : data(value), left(nullptr), right(nullptr) {}
};
template <typename T>
class BinarySearchTree{
    private:
        treeNode<T>* root;
        treeNode<T>* insert(treeNode<T>* node,const T& value){
            if(!node){
                return new treeNode<T>(value);
            }
            if(value<node->data){
                node->left = insert(node->left,value);
            }else if(value>node->data){
                node->right = insert(node->right,value);
            }else{
                return node;
            }
            return node;
        }
        treeNode<T>* remove(treeNode<T>* node,const T& value)
        {
            if(!node){
                return nullptr;
            }
            if(value<node->data){
                node->left = remove(node->left,value);
            }else if(value>node->data){
                node->right = remove(node->right,value);
            }else{
                if(!node->left){
                    treeNode<T>* temp = node->right;
                    delete node;
                    return temp;
                }else if(!node->right){
                    treeNode<T>* temp = node->left;
                    delete node;
                    return temp;
                }else{
                    treeNode<T>* temp = node->right;
                    while(temp->left){
                        temp = temp->left;
                    }
                    node->data = temp->data;
                    node->right = remove(node->right, temp->data);
                }
            }
            return node;
        }
        treeNode<T>* find(treeNode<T>* node,const T& value)
        {
            if(!node){
                return nullptr;
            }
            if(value<node->data){
                return find(node->left,value);
            }else if(value>node->data){
                return find(node->right,value);
            }else{
                return node;
            }
        }
        //应对宽字符情况
    
        

        void inOrderTraversal(treeNode<T>* node){
            if(node){
                inOrderTraversal(node->left);
                std::cout<<node->data<<"  with hash value"<<HashOfNode(node)<<std::endl;
                inOrderTraversal(node->right);
                
            }


        }
        
        void preOrderTraversal(treeNode<T>* node);
        void postOrderTraversal(treeNode<T>* node);
        
    public:
        BinarySearchTree() : root(nullptr) {}
        void insert(const T& value) {
            root = insert(root, value);
        }
        void remove(const T& value) {
            root = remove(root, value);
        }
        void inOrderTraversal() {
            inOrderTraversal(root);
        }
        void preOrderTraversal() {
            preOrderTraversal(root);
        }
        void postOrderTraversal() {
            postOrderTraversal(root);
        }
};


template<>
class BinarySearchTree<DialogueData> {
public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        destroyTree(root);
    }

    void insert(const DialogueData& value) {
        root = insertRec(root, value);
    }

    void inOrderTraversal() {
        inOrderTraversalRec(root);
    }

private:
    treeNode<DialogueData>* root;

    treeNode<DialogueData>* insertRec(treeNode<DialogueData>* node, const DialogueData& value) {
        if (node == nullptr) {
            return new treeNode<DialogueData>(value);
        }

        if (value < node->data) {
            node->left = insertRec(node->left, value);
        } else if (node->data < value) {
            node->right = insertRec(node->right, value);
        } else {
            // 如果用户输入相同，可以选择更新回复或不插入重复数据
            // 这里假设不插入重复的用户输入
        }
        return node;
    }

    void inOrderTraversalRec(treeNode<DialogueData>* node) {
        if (node != nullptr) {
            inOrderTraversalRec(node->left);
            // 输出节点数据
            std::wcout << L"用户: " << node->data.userInput << std::endl;
            std::wcout << L"助手: " << node->data.llmResponse << std::endl;
            std::wcout << L"------------------------" << std::endl;
            inOrderTraversalRec(node->right);
        }
    }

    void destroyTree(treeNode<DialogueData>* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};

template <typename T>
class AVLTreeNode {
public:
    T data;
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;

    AVLTreeNode(const T& value)
        : data(value), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree {
private:
    AVLTreeNode<T>* root;

    // 获取节点高度
    int getHeight(AVLTreeNode<T>* node) {
        return node ? node->height : 0;
    }

    // 计算平衡因子
    int getBalanceFactor(AVLTreeNode<T>* node) {
        return getHeight(node->left) - getHeight(node->right);
    }

    // 左旋转
    AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        // 更新高度
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    // 右旋转
    AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        // 更新高度
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    // 重新平衡节点
    AVLTreeNode<T>* rebalance(AVLTreeNode<T>* node) {
        // 更新高度
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalanceFactor(node);

        // 左子树高，进行右旋转
        if (balanceFactor > 1) {
            if (getBalanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // 右子树高，进行左旋转
        if (balanceFactor < -1) {
            if (getBalanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // 插入节点
    AVLTreeNode<T>* insert(AVLTreeNode<T>* node, const T& value) {
        if (!node)
            return new AVLTreeNode<T>(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        else
            return node; // 不允许重复值

        return rebalance(node);
    }

    // 删除节点
    AVLTreeNode<T>* remove(AVLTreeNode<T>* node, const T& value) {
        if (!node)
            return node;

        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {
            if (!node->left || !node->right) {
                AVLTreeNode<T>* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                AVLTreeNode<T>* temp = node->right;
                while (temp->left)
                    temp = temp->left;
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        if (!node)
            return node;

        return rebalance(node);
    }

    // 查找节点
    AVLTreeNode<T>* find(AVLTreeNode<T>* node, const T& value) {
        if (!node)
            return nullptr;

        if (value < node->data)
            return find(node->left, value);
        else if (value > node->data)
            return find(node->right, value);
        else
            return node;
    }

    // 中序遍历
    void inOrderTraversal(AVLTreeNode<T>* node) {
        if (node) {
            inOrderTraversal(node->left);
            std::cout << node->data << "  with hash value"<<HashOfNode(node)<<std::endl;
            inOrderTraversal(node->right);
        }
    }

    // 前序遍历
    void preOrderTraversal(AVLTreeNode<T>* node) {
        if (node) {
            std::cout << node->data << std::endl;
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    // 后序遍历
    void postOrderTraversal(AVLTreeNode<T>* node) {
        if (node) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            std::cout << node->data << std::endl;
        }
    }

public:
    AVLTree() : root(nullptr) {}

int HashOfNode(AVLTreeNode<T>* node) {
    if (node == nullptr) {
        return 0;
    }
    std::hash<T> hasher;
    size_t hashValue = hasher(node->data);
   
    return hashValue;
}
    void insert(const T& value) {
        root = insert(root, value);
    }

    void remove(const T& value) {
        root = remove(root, value);
    }

    void update(const T& oldValue, const T& newValue) {
        remove(oldValue);
        insert(newValue);
    }

    bool find(const T& value) {
        return find(root, value) != nullptr;
    }

    void inOrderTraversal() {
        inOrderTraversal(root);
    }

    void preOrderTraversal() {
        preOrderTraversal(root);
    }

    void postOrderTraversal() {
        postOrderTraversal(root);
    }
};
void testAVLTree() {
    AVLTree<int> avlTree;

    avlTree.insert(10);
    avlTree.insert(20);
    avlTree.insert(30);
    avlTree.insert(40);
    avlTree.insert(50);
    avlTree.insert(25);
    avlTree.insert(22);
    avlTree.insert(27);
    avlTree.insert(26);

    std::cout << "In-order traversal:" << std::endl;
    avlTree.inOrderTraversal();

    std::cout << "Pre-order traversal:" << std::endl;
    avlTree.preOrderTraversal();

    std::cout << "Post-order traversal:" << std::endl;
    avlTree.postOrderTraversal();
    cout<<endl;
    cout<<"test find(25)"<<endl;
    if(avlTree.find(25)){
        cout<<25<<" is found"<<endl;
    }else{
        cout<<25<<" is not found"<<endl;
    }
    cout<<"test remove(25)"<<endl;
    avlTree.remove(25);
    if(avlTree.find(25)){
        cout<<25<<" is found"<<endl;
    }else{
        cout<<25<<" is not found"<<endl;
    }

    cout<<"new inorder traversal:"<<endl;
    avlTree.inOrderTraversal();
    cout<<"test update"<<endl;
    avlTree.update(30,25);
    if(avlTree.find(30)){
        cout<<30<<" is found"<<endl;
    }else{
        cout<<30<<" is not found"<<endl;
    }
    cout<<"new inorder traversal:"<<endl;
    avlTree.inOrderTraversal();
}