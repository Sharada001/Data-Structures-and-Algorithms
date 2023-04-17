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
    // constructor
    BinarySearchTree() {
        head = nullptr;
    }

    // --------------------------------------------------------------------------------------

    // Inserting items to BST with given value
    
    node* create_node(int value) {
        // creates a new node with given value
        node* temp = new node;
        temp->data = value;
        temp->left = nullptr;
        temp->right = nullptr;
        return temp;
    }

    private:
    void add_single_item(node* top, int value) {
        // adds a new item to the tree
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
        // adds a new item to the tree (including head)
        if (head == nullptr) {
            head = create_node(value);
        }
        else {
            add_single_item(head,value);
        }
    }
    
    // -----------------------------------------------------------------------------------

    // searching for an item with given value

    private:
    node* search_item(node* top, int value) {
        // searches for an item with given value, starting from top
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
        // searches for first item with given value, starting from head
        if (head==nullptr) {
            return nullptr;
        }
        return search_item(head, value);
    }

    vector<node*> get_all_items(int value) {
        // searches for all items with given value, starting from head
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

    // -----------------------------------------------------------------------------------------

    // deleting all items from BST with the given value

    private:
    void swap_nodes(node* parentA, node* childA, node* parentB, node* childB) {
        // swaps positions of two nodes childA and childB in the tree
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
        // searches for item with minimum value, starting from top
        while (top->left != nullptr) {
            top = top-> left;
        }
        return top;
    }

    private:
    node* search_with_parent(node* top, int value, node* parent) {
        // searches for parent of item with given value, starting from top
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
        // deletes an item with given value from the tree
        if (top != nullptr) {
            node* tempParentA = search_with_parent(top, value, nullptr); // searches for item with value, starting from top
            node* tempChildA = search_item(top, value); // searches for parent of item, starting from top
            if (tempParentA == nullptr) {
                if (tempChildA == nullptr) {
                    // value is not in the tree case
                    return 0;
                }
                else {
                    // head == value case
                    if ((head->left == nullptr) && (head->right == nullptr)) {
                        // head is the only item in tree case
                        head =  nullptr;
                        return 1;
                    }
                    if (head->right == nullptr) {
                        // only right branch of head is empty case
                        head =  head->left;
                        return 1;
                    }
                    node* minNode = minimum_node(tempChildA->right);  // searches for item with minimum value, starting from childA.right
                    node* tempParentB = search_with_parent(tempChildA->right, minNode->data, tempChildA);
                    node* tempChildB = minNode;
                    if (tempChildA == tempParentB) {
                        // right branch has only one item case
                        tempChildB->left = tempChildA->left;
                        head = tempChildB;
                        return 1;
                    }
                    head = tempChildB;
                    tempParentB->left = tempChildB->right;
                    head->left = tempChildA->left;
                    head->right = tempChildA->right;
                    
                    return 1;
                }
            }
            else {
                if ((tempChildA->left == nullptr) && (tempChildA->right == nullptr)) {
                    // item with the value is a leaf case
                    
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
                    // right branch of item with value, is empty case
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
                    // right branch of item has only one item case
                    if (tempParentA->left == tempChildA) {
                        tempParentA->left = tempChildB;
                    } else {
                        tempParentA->right = tempChildB;
                    }
                    tempChildB->left = tempChildA->left;
                    return 1;
                }
                swap_nodes(tempParentA, tempChildA, tempParentB, tempChildB);   // positions of childA and childB within the tree, are swapped
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
        // deletes all items with given value from the tree
        int state = 1;
        while (state) {
            state = delete_single_item(head,value);
        }
    }

    private:
    node* delete_single_item_recursive(node* top, int value) {
        if (top==nullptr) return nullptr;
        else if (value < top->data) {
            top->left = delete_single_item_recursive(top->left, value);
        }
        else if (value > top->data) {
            top->right = delete_single_item_recursive(top->right, value);
        }
        else {
            if (top->left == nullptr) {
                node* temp = top->right;
                delete top;
                return temp;
            }
            else if (top->right == nullptr) {
                node* temp = top->left;
                delete top;
                return temp;
            }
            node* temp = minimum_node(top->right);
            top->data = temp->data;
            top->right = delete_single_item_recursive(top->right, temp->data);
        }
    }

    public:
    void delete_item_recursive(int value) {
        // deletes all items with given value from the tree
        node* state = nullptr;
        while (state) {
            state = delete_single_item_recursive(head,value);
        }
    }


    // ------------------------------------------------------------------------------------------

    // tree traversals

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

    //-------------------------------------------------------------------------------------------
};

int main(){
    
    BinarySearchTree binarySearchTree = BinarySearchTree();
    binarySearchTree.add_item(10);
    binarySearchTree.add_item(5);
    binarySearchTree.add_item(15);
    binarySearchTree.add_item(12);
    binarySearchTree.add_item(17);
    binarySearchTree.add_item(13);
    // cout << binarySearchTree.get_first_item(32)->data << endl;
    binarySearchTree.delete_item(10);
    binarySearchTree.traverse("in-order");
    return 0;
}
