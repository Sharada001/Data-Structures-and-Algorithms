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

    node* minimum_node(node* top) {
        while (top->left != nullptr) {
            top = top-> left;
        }
        return top;
    }

    node* search_with_parent(node* top, int value, node* parent) {
        if (value < top->data) {
            if (top->left == nullptr) return nullptr;
            return search_with_parent(top->left, value, top);
        }
        else if (value > top->data) {
            if (top->right == nullptr) return nullptr;
            return search_with_parent(top->right, value, top);
        }
        else {
            return parent;
        }
    }

    int delete_single_item(node* top, int value) {
        if (top != nullptr) {
            node* tempParentA = search_with_parent(top, value, nullptr);
            node* tempChildA = search_item(top, value);
            if (tempParentA == nullptr) {
                if (tempChildA == nullptr) {
                    // not found case
                    return 0;
                }
                else {
                    // head == value case
                    if ((head->left == nullptr) && (head->right == nullptr)) {
                        head =  nullptr;
                        return 1;
                    }
                    if (head->right == nullptr) {
                        head =  head->left;
                        return 1;
                    }
                    node* minNode = minimum_node(tempChildA->right);
                    node* tempParentB = search_with_parent(tempChildA->right, minNode->data, tempChildA);
                    node* tempChildB = minNode;
                    if (tempChildA == tempParentB) {
                        tempChildB->left = tempChildA->left;
                        head = tempChildB;
                        return 1;
                    }
                    head = tempChildB;
                    head->left = tempChildA->left;
                    head->right = tempChildA->right;
                    tempParentB->left = nullptr;
                    return 1;
                }
            }
            else {
                if ((tempChildA->left == nullptr) && (tempChildA->right == nullptr)) {
                    
                    if (tempParentA->left == tempChildA) {
                        tempParentA->left = nullptr;
                        return 1;
                    }
                    else {
                        tempParentA->right = nullptr;
                        return 1;
                    }
                }
                if (tempChildA->right == nullptr) {
                    if (tempParentA->left == tempChildA) {
                        tempParentA->left = tempChildA->left;
                        return 1;
                    }
                    else {
                        tempParentA->right = tempChildA->left;
                        return 1;
                    }
                }
                node* minNode = minimum_node(tempChildA->right);
                node* tempParentB = search_with_parent(tempChildA->right, minNode->data, tempChildA);
                node* tempChildB = minNode;
                if (tempChildA == tempParentB) {
                    if (tempParentA->left == tempChildA) {
                        tempParentA->left = tempChildB;
                    } else {
                        tempParentA->right = tempChildB;
                    }
                    tempChildB->left = tempChildA->left;
                    return 1;
                }
                swap_nodes(tempParentA, tempChildA, tempParentB, tempChildB);
                if (tempParentB->left == tempChildA) {
                    cout << "++++++++++++" << endl;
                    tempParentB->left = nullptr;
                } else {
                    cout << "------------" << endl;
                    tempParentB->right = nullptr;
                }
                return 1;
            }
        }
        else {
            return 0;
        }

    }

    void delete_item(node* top, int value) {
        int state = 1;
        while (state) {
            state = delete_single_item(head,value);
        }
        
    }

    void in_order_traversal (node* top) {
        if (top != nullptr) {
            if (top->left != nullptr) {
                in_order_traversal (top->left);
            }
            cout << top->data << " ";
            if (top->right != nullptr) {
                in_order_traversal (top->right);
            }
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
    binarySearchTree.add_item(binarySearchTree.head, 12);
    binarySearchTree.add_item(binarySearchTree.head, 17);
    binarySearchTree.add_item(binarySearchTree.head, 25);
    binarySearchTree.add_item(binarySearchTree.head, 18);
    binarySearchTree.add_item(binarySearchTree.head, 11);

    binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    // binarySearchTree.swap_nodes(binarySearchTree.head, binarySearchTree.head->left, binarySearchTree.head->left->right->left, binarySearchTree.head->left->right->left->left);
    // binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    // cout<< binarySearchTree.minimum_node(binarySearchTree.head->left->right)->data << endl;
    binarySearchTree.delete_item(binarySearchTree.head, 15);
    binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    binarySearchTree.delete_item(binarySearchTree.head, 17);
    binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    binarySearchTree.delete_item(binarySearchTree.head, 18);
    binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    binarySearchTree.delete_item(binarySearchTree.head, 30);
    binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    binarySearchTree.delete_item(binarySearchTree.head, 18);
    binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    binarySearchTree.delete_item(binarySearchTree.head, 25);
    binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    binarySearchTree.delete_item(binarySearchTree.head, 10);
    binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    binarySearchTree.delete_item(binarySearchTree.head,11);
    binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    binarySearchTree.delete_item(binarySearchTree.head, 12);
    binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    binarySearchTree.delete_item(binarySearchTree.head, 5);
    binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    binarySearchTree.delete_item(binarySearchTree.head, 20);
    binarySearchTree.in_order_traversal(binarySearchTree.head); cout<< endl;
    return 0;
}
