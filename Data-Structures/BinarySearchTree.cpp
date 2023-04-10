#include <iostream>
using namespace std;

struct node {
    node* left;
    node* right;
    int data;
};

class BinarySearchTree {
    public:
    node* head;
    
    public:
    BinarySearchTree() {
        head = nullptr;
    }

    node* create_node(int value) {
        node* temp = new node;
        temp->data = value;
        temp->left = nullptr;
        temp->right = nullptr;
        return temp;
    }

    void add_item(node* top, int value) {
        if (value <= top->data) {
            if (top->left == nullptr) {
                top->left = create_node(value);
                return;
            }
            add_item(top->left, value);
        }
        else {
            if (top->right == nullptr) {
                top->right = create_node(value);
                return;
            }
            add_item(top->right, value);
        }
    }

    node* search_item(node* top, int value) {
        if (value < top->data) {
            if (top->left == nullptr) return nullptr;
            return search_item(top->left, value);
        }
        else if (value > top->data) {
            if (top->right == nullptr) return nullptr;
            return search_item(top->right, value);
        }
        else {
            return top;
        }
    }
};

int main(){

    BinarySearchTree binarySearchTree = BinarySearchTree();
    binarySearchTree.head = new node;
    binarySearchTree.head->data = 20;
    binarySearchTree.head->left = nullptr;
    binarySearchTree.head->left = nullptr;

    binarySearchTree.head->left = new node;
    binarySearchTree.head->left->data = 10;
    binarySearchTree.head->left->left = nullptr;
    binarySearchTree.head->left->right = nullptr;

    binarySearchTree.head->right = new node;
    binarySearchTree.head->right->data = 30;
    binarySearchTree.head->right->left = nullptr;
    binarySearchTree.head->right->right = nullptr;

    binarySearchTree.head->left->left = new node;
    binarySearchTree.head->left->left->data = 5;
    binarySearchTree.head->left->left->left = nullptr;
    binarySearchTree.head->left->left->right = nullptr;

    binarySearchTree.head->left->right = new node;
    binarySearchTree.head->left->right->data = 15;
    binarySearchTree.head->left->right->left = nullptr;
    binarySearchTree.head->left->right->right = nullptr;

    cout << binarySearchTree.search_item(binarySearchTree.head, 15) << endl;
    cout<< endl;
    binarySearchTree.add_item(binarySearchTree.head, 12);
    cout<< endl;
    binarySearchTree.add_item(binarySearchTree.head, 17);
    cout<< endl;
    binarySearchTree.add_item(binarySearchTree.head, 25);
    cout<< endl;
    binarySearchTree.add_item(binarySearchTree.head, 18);
    cout<< endl;
    binarySearchTree.add_item(binarySearchTree.head, 11);
    cout<< endl;
    cout << binarySearchTree.search_item(binarySearchTree.head, 17) << endl;
    return 0;
}
