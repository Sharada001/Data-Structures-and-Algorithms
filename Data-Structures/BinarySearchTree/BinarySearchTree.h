#include <iostream>
#include <vector>
using namespace std;

struct node {
    node* left;
    node* right;
    int data;
};

class BinarySearchTree {
    private:
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

    private:
    void add_single_item(node* top, int value) {
        if (value <= top->data) {
            if (top->left == nullptr) {
                top->left = create_node(value);
                return;
            }
            add_single_item(top->left, value);
        }
        else {
            if (top->right == nullptr) {
                top->right = create_node(value);
                return;
            }
            add_single_item(top->right, value);
        }
    }

    public:
    void add_item(int value) {
        if (head == nullptr) {
            head = create_node(value);
        }
        else {
            add_single_item(head,value);
        }
    }

    private:
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

    public:
    node* get_first_item(int value) {
        if (head==nullptr) {
            return nullptr;
        }
        return search_item(head, value);
    }

    vector<node*> get_all_items(int value) {
        cout << "--------";
        vector<node*> nodes;
        
        if (head!=nullptr) {
            node* nodePtr = search_item(head, value);
            if (nodePtr==nullptr) return nodes;
            while (nodePtr!=nullptr) {
                
                nodes.push_back(nodePtr);
                nodePtr = search_item(nodePtr->left, value);
            }
            return nodes;

        }
        else return nodes;
    }

    private:
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

    private:
    node* minimum_node(node* top) {
        while (top->left != nullptr) {
            top = top-> left;
        }
        return top;
    }

    private:
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

    private:
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
                    tempParentB->left = nullptr;
                } else {
                    tempParentB->right = nullptr;
                }
                return 1;
            }
        }
        else {
            return 0;
        }

    }

    public:
    void delete_item(int value) {
        int state = 1;
        while (state) {
            state = delete_single_item(head,value);
        }
    }

    private:
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

    private:
    void pre_order_traversal (node* top) {
        if (top != nullptr) {
            cout << top->data << " ";
            if (top->left != nullptr) {
                pre_order_traversal (top->left);
            }
            if (top->right != nullptr) {
                pre_order_traversal (top->right);
            }
        }
    }

    private:
    void post_order_traversal (node* top) {
        if (top != nullptr) {
            if (top->left != nullptr) {
                post_order_traversal (top->left);
            }
            if (top->right != nullptr) {
                post_order_traversal (top->right);
            }
            cout << top->data << " ";
        }
    }

    public:
    void traverse(string order) {
        if (order == "pre-order") {
            pre_order_traversal(head);
        }
        else if (order == "post-order") {
            post_order_traversal (head);
        }
        else {
            in_order_traversal(head);
        }
        cout << endl;
    }

};
