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

    void swap_nodes(node* parentA, node* childA, node* parentB, node* childB) {
        if ((parentA->left==childA) && (parentB->left==childB)) {
            parentA->left = childB;
            parentB->left = childA;
        }
        else if ((parentA->right==childA) && (parentB->left==childB)) {
            parentA->right = childB;
            parentB->left = childA;
        }
        else if ((parentA->left==childA) && (parentB->right==childB)) {
            parentA->left = childB;
            parentB->right = childA;
        }
        else {
            parentA->right = childB;
            parentB->right = childA;
        }
        node* templeft = childB->left;
        node* tempright = childB->right;
        childB->left = childA->left;
        childB->right = childA->right;
        childA->left = templeft;
        childA->right = tempright;
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

    node* minimum_node(node* top) {
        while (top->left != nullptr) {
            top = top-> left;
        }
        return top;
    }

    void in_order_traversal (node* top) {
        if (top->left != nullptr) {
            in_order_traversal (top->left);
        }
        cout << top->data << " ";
        if (top->right != nullptr) {
            in_order_traversal (top->right);
        }
        return;
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
    binarySearchTree.add_item(binarySearchTree.head, 12);
    binarySearchTree.add_item(binarySearchTree.head, 17);
    binarySearchTree.add_item(binarySearchTree.head, 25);
    binarySearchTree.add_item(binarySearchTree.head, 18);
    binarySearchTree.add_item(binarySearchTree.head, 11);

    binarySearchTree.in_order_traversal(binarySearchTree.head);
    cout<< endl;
    binarySearchTree.swap_nodes(binarySearchTree.head, binarySearchTree.head->left, binarySearchTree.head->left->right->left, binarySearchTree.head->left->right->left->left);
    binarySearchTree.in_order_traversal(binarySearchTree.head);
    cout<< endl;
    cout<< binarySearchTree.minimum_node(binarySearchTree.head->left->right)->data << endl;
    return 0;
}
