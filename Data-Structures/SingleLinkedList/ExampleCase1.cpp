#include "SingleLinkedList.h"
#include <vector>
using namespace std;

int main(){
    SingleLinkedList singleLinkedList = SingleLinkedList();
    vector<int> numbers = {3,400,64,10,117,221,237,163,790,34,20,30,39,441,567,200,56,117} ;
    for (int i=0; i<numbers.size(); i++) {
        singleLinkedList.insert(numbers[i]);
    }
    singleLinkedList.display();

}