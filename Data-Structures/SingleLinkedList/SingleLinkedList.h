# include <iostream>
using namespace std;

struct item {
    int data;
    item *next;
};

class SingleLinkedList {
    private :
        item *head;
    
    public :
        SingleLinkedList() {
            // constructor
            head = NULL;
        }

        void insert(int data) {
            // create a new item
            item *newItem = new item;
            newItem->data = data;
            newItem->next = NULL;

            if (head == NULL) {
                head = newItem;
            } 
            else {
                item *temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newItem;
            }
        }

        void display() {
            // display all items
            item *temp = head;
            while (temp != NULL) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }

        void deleteItem(int data) {
            // delete a single item with given value
            item *temp = head;
            item *prev = NULL;
            while (temp != NULL) {
                if (temp->data == data) {
                    if (prev == NULL) {
                        head = temp->next;
                    } else {
                        prev->next = temp->next;
                    }
                    delete temp;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
        }

        void reverse() {
            item *prev = NULL;
            item *current = head;
            item *next = NULL;

            while (current != NULL) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            head = prev;
        }

        void reverseRecursion(item *current, item *prev) {
            if (current->next == NULL) {
                head = current;
                current->next = prev;
                return;
            }
            item *next = current->next;
            current->next = prev;
            reverseRecursion(next, current);
        }

        void reverseRecursion() {
            reverseRecursion(head, NULL);
        }

};