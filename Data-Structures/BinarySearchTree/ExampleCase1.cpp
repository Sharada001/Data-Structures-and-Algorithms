#include "BST.h"
#include <vector>

int main() {
    BinarySearchTree binarySearchTree = BinarySearchTree();
    vector<int> numbers = {3,400,64,10,117,221,237,163,790,34,20,30,39,441,567,200,56,117} ;
    for (int i=0; i<numbers.size(); i++) {
        binarySearchTree.add_item(numbers[i]);
    }
    binarySearchTree.traverse("pre-order");
    // all items have been added right to the root node.
    // which causes inefficiency in this unbalaneced BST implementation.
    
}